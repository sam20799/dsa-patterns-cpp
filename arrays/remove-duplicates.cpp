/*
Problem: Remove Duplicates from Sorted Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
Pattern: Two Pointers
Difficulty: Easy
*/

#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int slow = 0;
        for (int fast = 1; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != nums[slow]) {
                nums[++slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};
