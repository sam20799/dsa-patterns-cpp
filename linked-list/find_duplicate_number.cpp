/*
Problem: 287. Find the Duplicate Number
Platform: LeetCode
Problem Link: http://leetcode.com/problems/find-the-duplicate-number/description/
Pattern: Linked List
Difficulty: Medium
*/

#include <iostream>
using namespace std;

int findDuplicate(vector<int> &nums){
    int slow = 0;
    int fast = 0;
    while(true){
        slow = nums[slow];
        fast = nums[fast];
        fast = nums[fast];
        if (slow == fast){
            slow = 0;
            while(slow != fast){
                slow = nums[slow];
                fast = nums[fast];
            }
            return slow;
        }
    }
}


int main(){
    vector<int>arr= {1,3,4,2,2};
    cout<<findDuplicate(arr);
}


