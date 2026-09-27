/*
Problem: Valid Anagram
Platform: LeetCode
Problem Link: https://leetcode.com/problems/valid-anagram/
Pattern: Hashing
Difficulty: Easy
*/

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;
        for (char c : t) {
            if (--freq[c] < 0) return false;
        }
        return true;
    }
};
