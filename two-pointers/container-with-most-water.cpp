/*
Problem: Container With Most Water
Platform: LeetCode
Problem Link: https://leetcode.com/problems/container-with-most-water/
Pattern: Two Pointers
Difficulty: Medium
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& h) {
        int l=0, r=h.size()-1, best=0;
        while (l<r) {
            best = max(best, (r-l)*min(h[l],h[r]));
            if (h[l]<h[r]) l++; else r--;
        }
        return best;
    }
};
