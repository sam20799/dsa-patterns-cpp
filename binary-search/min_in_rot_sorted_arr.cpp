/*
Problem: 153. Find Minimum in Rotated Sorted Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
Pattern: Binary Search
Difficulty: Medium
*/


#include <iostream>
using namespace std;

int findMin(vector<int>& nums) {
        int n =nums.size();
        int low = 0;
        int high = n-1;
        int ans = -1;
        while(low<=high){
            int mid = (low+high)/2;
            if(nums[mid]>nums[n-1]) low = mid+1;
            else{
                ans = nums[mid];
                high = mid-1;
            }
        }
        return ans;
    }

    //turning point arr[mid]<arr[n-1] 
    // arr[mid] > arr[n-1] -> [3,4,5,1,2] ->[yes,yes,yes,no,no]
    // find first occurance of no its the head

int main(){
    vector<int> nums = {3, 4, 5, 1, 2};
    cout<<findMin(nums);

}