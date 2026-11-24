/*
Problem: 33. Search in Rotated Sorted Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/search-in-rotated-sorted-array/description/
Pattern: Binary Search
Difficulty: Medium
*/


#include <iostream>
using namespace std;

int newhead(vector<int>& nums){
    int n = nums.size();
    int low = 0;
    int high = n-1;
    int ans = -1;
    while(low<=high){
        int mid = (low+high)/2;
        if(nums[mid]>nums[n-1]) low = mid+1;
        else{
            ans = mid;
            high = mid-1;
        } 
    }
    return ans;
}

int search(vector<int>& nums, int target) {
    int head = newhead(nums);
    int low = 0;
    int high = head-1;
    int ans = -1;
    while(low<=high){
        int mid = (low+high)/2;
        if(nums[mid] == target) return mid;
        if(nums[mid]< target) low = mid+1;
        else high = mid-1;
    }
    
    low = head;
    high = nums.size()-1;

    while(low<=high){
    int mid = (low+high)/2;
    if(nums[mid]== target)  return mid;
    if(nums[mid]< target) low = mid+1;
    else high = mid-1;
    }
    return ans;
}

int main(){
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    cout<<search(nums,target);

}