/*
Problem: 209. Minimum Size Subarray Sum
Platform: LeetCode
Problem Link: https://leetcode.com/problems/minimum-size-subarray-sum/description/
Pattern: Sliding Window
Difficulty: Medium
*/

#include <iostream>
using namespace std;
int minSubArrLen(int target, vector<int>&nums){
    int low = 0;
    int sum = 0;
    int res = INT_MAX;
    for(int high=0;high<nums.size();high++){
        sum += nums[high];
        while(sum>=target){
            int len = high-low+1;
            res = min(len,res);
            sum -= nums[low];
            low++;
        }
    }
    return (res==INT_MAX?0:res);

}



int main(){
    int n;
    cin>>n;

    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int target;
    cin>>target;
    
    int res = minSubArrLen(target,arr);
    cout<<res;

    return 0;
}
