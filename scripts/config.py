"""
Configuration for the DSA progress tracking system.

Edit TOPICS below to add/rename topics, change folder names, or update targets.
Nothing else in update_progress.py needs to change when you edit this file.
"""

from collections import OrderedDict

# folder_name -> (Display Name, target_count)
# `folder_name` must match the actual directory name inside the repo root.
TOPICS = OrderedDict([
    ("arrays",                 ("Arrays",                      20)),
    ("hashing",                ("Hashing",                      15)),
    ("two-pointers",           ("Two Pointers",                 15)),
    ("sliding-window",         ("Sliding Window",               15)),
    ("stack",                  ("Stack",                        10)),
    ("queue-deque",            ("Queue & Deque",                 5)),
    ("binary-search",          ("Binary Search",                15)),
    ("linked-list",            ("Linked List",                  10)),
    ("recursion-backtracking", ("Recursion & Backtracking",     10)),
    ("trees-bst",              ("Trees & BST",                  15)),
    ("heaps",                  ("Heap / Priority Queue",        10)),
    ("greedy",                 ("Greedy",                       10)),
    ("graphs",                 ("Graphs",                       15)),
    ("dynamic-programming",    ("Dynamic Programming",          20)),
    ("bit-manipulation",       ("Bit Manipulation",              5)),
    ("tries",                  ("Tries",                         5)),
])

# Total problems targeted across all topics (used for the overall progress bar).
TOTAL_TARGET = sum(target for _, target in TOPICS.values())

# Number of characters used to render each ASCII progress bar, e.g. [██████░░░░]
BAR_LENGTH = 20

# Path to the README, relative to the repository root.
README_PATH = "README.md"

# A solution filename is skipped (not counted, not touched) if its lowercase
# name contains any of these substrings. Keeps test/scratch files out of the count.
IGNORE_SUBSTRINGS = (
    "test_",
    "_test",
    "tmp_",
    "_tmp",
    ".tmp",
    "scratch",
    "draft",
)
