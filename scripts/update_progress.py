#!/usr/bin/env python3
"""
update_progress.py
-------------------
Single-command DSA progress automation for dsa-patterns-cpp.

What it does, every time you run it:
  1. Scans the topic folders for solved .cpp files.
  2. Recomputes topic-wise and overall progress bars.
  3. Rewrites only the progress section of README.md (everything else untouched).
  4. Figures out what actually changed (new / modified / deleted solutions,
     README-only changes, or nothing).
  5. Stages ONLY the relevant files (topic folders + README.md) -- never
     unrelated files you happen to have modified elsewhere in the repo.
  6. Builds a Conventional Commit message from the changes.
  7. Commits and pushes -- unless there is nothing to commit, in which case
     it does nothing (no empty commits, ever).

Usage:
    python3 scripts/update_progress.py
    python3 scripts/update_progress.py --dry-run   # preview only, no git writes

Only uses the Python standard library.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

import scripts.config as config


# --------------------------------------------------------------------------
# Paths
# --------------------------------------------------------------------------

def repo_root() -> Path:
    """The repository root is the parent of the scripts/ directory."""
    return Path(__file__).resolve().parent.parent


# --------------------------------------------------------------------------
# Scanning solution files
# --------------------------------------------------------------------------

def is_valid_solution_file(path: Path) -> bool:
    """A file counts as a solved problem if it's a real, non-scratch .cpp file."""
    name = path.name
    if path.suffix.lower() != ".cpp":
        return False
    if name.startswith("."):
        return False
    lower = name.lower()
    if any(token in lower for token in config.IGNORE_SUBSTRINGS):
        return False
    # Duplicate-looking files, e.g. "two-sum copy.cpp" or "two-sum (1).cpp"
    if re.search(r"\(\d+\)$", path.stem.strip()):
        return False
    if lower.endswith(" copy.cpp") or " copy " in lower:
        return False
    return True


def scan_topics(root: Path) -> dict[str, list[Path]]:
    """Return {topic_folder: [sorted relative .cpp paths]} for every configured topic."""
    results: dict[str, list[Path]] = {}
    for folder in config.TOPICS:
        topic_dir = root / folder
        files: list[Path] = []
        if topic_dir.is_dir():
            for p in sorted(topic_dir.rglob("*.cpp")):
                if p.is_file() and is_valid_solution_file(p):
                    files.append(p.relative_to(root))
        results[folder] = files
    return results


# --------------------------------------------------------------------------
# Metadata extraction (best-effort; used only for commit messages)
# --------------------------------------------------------------------------

_META_FIELDS = ("Problem", "Platform", "Problem Link", "Pattern", "Difficulty")


def parse_metadata(root: Path, rel_path: Path) -> dict:
    """Pull the leading /* ... */ metadata block out of a solution file, if present."""
    meta: dict = {}
    try:
        text = (root / rel_path).read_text(encoding="utf-8", errors="ignore")
    except OSError:
        return meta

    block_match = re.search(r"/\*(.*?)\*/", text, re.DOTALL)
    block = block_match.group(1) if block_match else text[:500]

    for field in _META_FIELDS:
        m = re.search(rf"^\s*{re.escape(field)}\s*:\s*(.+?)\s*$", block, re.MULTILINE)
        if m:
            meta[field] = m.group(1).strip()
    return meta


def guess_problem_name(root: Path, rel_path: Path) -> str:
    """Human-friendly problem name: metadata if available, else the filename."""
    meta = parse_metadata(root, rel_path)
    if meta.get("Problem"):
        return meta["Problem"]
    stem = rel_path.stem.replace("-", " ").replace("_", " ").strip()
    return stem[:1].upper() + stem[1:] if stem else rel_path.name


# --------------------------------------------------------------------------
# Progress bar rendering
# --------------------------------------------------------------------------

def make_bar(count: int, target: int, length: int = None) -> tuple[str, int]:
    length = length or config.BAR_LENGTH
    if target <= 0:
        return "░" * length, 0
    pct = int(round((count / target) * 100))
    filled = int(round((min(count, target) / target) * length))
    filled = max(0, min(length, filled))
    bar = "█" * filled + "░" * (length - filled)
    return bar, pct


# --------------------------------------------------------------------------
# README rendering
# --------------------------------------------------------------------------

TOPIC_START = "<!-- PROGRESS:START -->"
TOPIC_END = "<!-- PROGRESS:END -->"
OVERALL_START = "<!-- OVERALL:START -->"
OVERALL_END = "<!-- OVERALL:END -->"

DEFAULT_README = """# DSA Patterns in C++

A structured collection of ~200 Data Structures & Algorithms problems
(LeetCode / GeeksforGeeks), solved in C++ and organized by pattern.

## 📊 Progress

{topic_start}
{topic_block}
{topic_end}

## 🎯 Overall Progress

{overall_start}
{overall_block}
{overall_end}

## 🧠 Focus

- Pattern recognition
- Problem solving
- Time & space complexity
- Interview preparation
"""


def render_topic_block(stats: list[dict]) -> str:
    lines = []
    for s in stats:
        bar, pct = make_bar(s["count"], s["target"])
        lines.append(f"### {s['name']}\n")
        lines.append(f"{s['count']} / {s['target']}\n")
        lines.append(f"[{bar}] {pct}%\n")
    return "\n".join(lines).rstrip()


def render_overall_block(solved: int, target: int) -> str:
    bar, pct = make_bar(solved, target, length=max(config.BAR_LENGTH, 20))
    return f"{solved} / {target} Problems\n\n[{bar}] {pct}%"


def build_readme(existing: str | None, topic_stats: list[dict], solved: int, target: int) -> str:
    topic_block = render_topic_block(topic_stats)
    overall_block = render_overall_block(solved, target)

    if existing is None:
        return DEFAULT_README.format(
            topic_start=TOPIC_START, topic_block=topic_block, topic_end=TOPIC_END,
            overall_start=OVERALL_START, overall_block=overall_block, overall_end=OVERALL_END,
        )

    content = existing

    def replace_between(text: str, start: str, end: str, new_body: str) -> str:
        pattern = re.compile(re.escape(start) + r".*?" + re.escape(end), re.DOTALL)
        replacement = f"{start}\n{new_body}\n{end}"
        if pattern.search(text):
            return pattern.sub(lambda _m: replacement, text)
        # Markers missing from an existing README: don't guess where to inject,
        # leave the file alone for this section rather than risk corrupting it.
        return text

    if TOPIC_START in content and TOPIC_END in content:
        content = replace_between(content, TOPIC_START, TOPIC_END, topic_block)
    if OVERALL_START in content and OVERALL_END in content:
        content = replace_between(content, OVERALL_START, OVERALL_END, overall_block)

    return content


# --------------------------------------------------------------------------
# Git helpers (subprocess with argument lists -- never shell strings)
# --------------------------------------------------------------------------

class GitError(RuntimeError):
    pass


def run_git(args: list[str], root: Path, check: bool = False) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["git", *args],
        cwd=root,
        capture_output=True,
        text=True,
        check=check,
    )


def is_git_repo(root: Path) -> bool:
    r = run_git(["rev-parse", "--is-inside-work-tree"], root)
    return r.returncode == 0 and r.stdout.strip() == "true"


def current_branch(root: Path) -> str | None:
    r = run_git(["symbolic-ref", "--short", "-q", "HEAD"], root)
    if r.returncode != 0:
        return None  # detached HEAD or no commits yet
    return r.stdout.strip()


def has_remote(root: Path) -> str | None:
    r = run_git(["remote"], root)
    remotes = [line.strip() for line in r.stdout.splitlines() if line.strip()]
    if not remotes:
        return None
    return "origin" if "origin" in remotes else remotes[0]


def git_status(root: Path) -> list[tuple[str, str, str | None]]:
    """Parse `git status --porcelain -z` robustly (handles spaces/renames)."""
    r = run_git(["status", "--porcelain=v1", "--untracked-files=all", "-z"], root)
    entries: list[tuple[str, str, str | None]] = []
    if not r.stdout:
        return entries
    tokens = r.stdout.split("\0")
    i = 0
    while i < len(tokens):
        tok = tokens[i]
        i += 1
        if not tok:
            continue
        code = tok[:2]
        path = tok[3:]
        if code[0] == "R" or code[1] == "R":
            # rename: next token is the old path
            old_path = tokens[i] if i < len(tokens) else None
            i += 1
            entries.append((code, path, old_path))
        else:
            entries.append((code, path, None))
    return entries


def is_relevant_path(rel_path: str) -> bool:
    """README.md, or anything inside a configured topic folder."""
    if rel_path == config.README_PATH:
        return True
    top = rel_path.split("/", 1)[0]
    return top in config.TOPICS


def stage_files(root: Path, paths: list[str]) -> None:
    if not paths:
        return
    run_git(["add", "--", *paths], root, check=True)


def commit(root: Path, title: str, body: str | None = None) -> None:
    args = ["commit", "-m", title]
    if body:
        args += ["-m", body]
    run_git(args, root, check=True)


def push(root: Path) -> subprocess.CompletedProcess:
    return run_git(["push"], root)


# --------------------------------------------------------------------------
# Commit message generation
# --------------------------------------------------------------------------

def topic_of(rel_path: str) -> str:
    return rel_path.split("/", 1)[0]


def build_commit_message(root: Path, new_files, modified_files, deleted_files, readme_only: bool):
    """Returns (title, body_or_None) or None if there's nothing worth committing."""

    cpp_new = [p for p in new_files if p.endswith(".cpp")]
    cpp_modified = [p for p in modified_files if p.endswith(".cpp")]
    cpp_deleted = [p for p in deleted_files if p.endswith(".cpp")]

    if cpp_new:
        if len(cpp_new) == 1:
            rel = cpp_new[0]
            topic = topic_of(rel)
            problem = guess_problem_name(root, Path(rel))
            return (f"feat({topic}): solve {problem}", None)
        else:
            body_lines = []
            for rel in cpp_new:
                topic = topic_of(rel)
                problem = guess_problem_name(root, Path(rel))
                body_lines.append(f"- {topic}: {problem}")
            return (f"feat(dsa): add {len(cpp_new)} new problem solutions", "\n".join(body_lines))

    if cpp_deleted and not cpp_modified:
        return (f"chore(dsa): remove {len(cpp_deleted)} solution file(s)", None)

    if cpp_modified:
        return ("refactor(dsa): update existing solution(s)", None)

    if readme_only:
        return ("docs: update DSA progress", None)

    return None


# --------------------------------------------------------------------------
# Summary printing
# --------------------------------------------------------------------------

def print_summary(topic_stats: list[dict], solved: int, target: int) -> None:
    print("DSA Progress Updated\n")
    name_width = max((len(s["name"]) for s in topic_stats), default=10)
    for s in topic_stats:
        _, pct = make_bar(s["count"], s["target"])
        print(f"{s['name']:<{name_width}}  {s['count']:>3}/{s['target']:<3}  {pct:>3}%")
    print()
    _, overall_pct = make_bar(solved, target)
    print(f"{'Overall':<{name_width}}  {solved:>3}/{target:<3}  {overall_pct:>3}%")
    print()


# --------------------------------------------------------------------------
# Main
# --------------------------------------------------------------------------

def main() -> int:
    parser = argparse.ArgumentParser(description="Update DSA progress README and push a commit.")
    parser.add_argument("--dry-run", action="store_true",
                         help="Update README and show what would be committed, but don't touch git.")
    args = parser.parse_args()

    root = repo_root()
    readme_path = root / config.README_PATH

    # 1-2. Scan solutions
    topic_files = scan_topics(root)
    topic_stats = []
    solved_total = 0
    for folder, (name, target) in config.TOPICS.items():
        count = len(topic_files[folder])
        solved_total += count
        if count > target:
            print(f"⚠️  Warning: '{name}' has {count} solutions, exceeding its target of {target}.")
        topic_stats.append({"folder": folder, "name": name, "count": count, "target": target})

    # 3-6. Update README (only the marked sections; rest is preserved byte-for-byte)
    existing = readme_path.read_text(encoding="utf-8") if readme_path.exists() else None
    new_readme = build_readme(existing, topic_stats, solved_total, config.TOTAL_TARGET)
    readme_changed = existing != new_readme

    if readme_changed:
        readme_path.write_text(new_readme, encoding="utf-8")

    print_summary(topic_stats, solved_total, config.TOTAL_TARGET)
    print("README.md updated successfully." if readme_changed else "README.md already up to date.")
    print()

    if args.dry_run:
        print("(--dry-run) Skipping git add/commit/push.")
        return 0

    # 7. Git safety checks
    if not is_git_repo(root):
        print("Not inside a git repository -- skipping commit/push.")
        print("Run 'git init' in the repo root to enable automatic commits.")
        return 0

    branch = current_branch(root)
    if branch is None:
        print("⚠️  HEAD is detached (not on a branch) -- skipping commit/push for safety.")
        print("Run 'git checkout <branch>' first, then re-run this script.")
        return 0
    print(f"On branch: {branch}")

    remote = has_remote(root)
    if remote is None:
        print("⚠️  No git remote configured -- will commit locally but skip 'git push'.")
        print("Add one with: git remote add origin <url>")

    # Figure out what changed
    status = git_status(root)
    new_files, modified_files, deleted_files = [], [], []
    unrelated = []

    for code, path, old_path in status:
        index_status, tree_status = code[0], code[1]
        relevant = is_relevant_path(path) or (old_path and is_relevant_path(old_path))
        if not relevant:
            unrelated.append(path)
            continue
        if code == "??":
            new_files.append(path)
        elif index_status == "R" or tree_status == "R":
            modified_files.append(path)
        elif index_status == "D" or tree_status == "D":
            deleted_files.append(path)
        elif index_status == "A":
            new_files.append(path)
        else:
            modified_files.append(path)

    readme_only = readme_changed and config.README_PATH in (new_files + modified_files)

    relevant_paths = sorted(set(new_files + modified_files + deleted_files))
    # README may have changed on disk without yet showing in `git status`
    # if this is the very first run before any git add; re-check explicitly.
    if readme_changed and config.README_PATH not in relevant_paths:
        # confirm git actually sees it as changed too
        recheck = git_status(root)
        if any(p == config.README_PATH for _, p, _ in recheck):
            relevant_paths.append(config.README_PATH)
            relevant_paths = sorted(set(relevant_paths))

    if unrelated:
        print("\nℹ️  Ignoring unrelated changes (not part of this commit):")
        for p in unrelated:
            print(f"   - {p}")

    if not relevant_paths:
        print("\nNo new or changed solutions/README -- nothing to commit.")
        return 0

    print("\nFiles that will be committed:")
    for p in relevant_paths:
        print(f"   - {p}")

    msg = build_commit_message(root, new_files, modified_files, deleted_files, readme_only)
    if msg is None:
        print("\nNo meaningful changes detected -- skipping commit.")
        return 0
    title, body = msg

    # 8. Stage, commit, push
    try:
        stage_files(root, relevant_paths)
        commit(root, title, body)
    except subprocess.CalledProcessError as e:
        print("\n❌ Git commit failed:")
        print(e.stderr or e.stdout)
        return 1

    print(f"\n✅ Committed: {title}")

    if remote is None:
        print("Skipped push (no remote configured).")
        return 0

    result = push(root)
    if result.returncode != 0:
        print("\n❌ 'git push' failed:")
        print(result.stderr.strip() or result.stdout.strip() or "(no error output from git)")
        print("\nYour commit was created locally but NOT pushed. Resolve the issue above, then run:")
        print("    git push")
        return 1

    print("✅ Pushed to remote.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
