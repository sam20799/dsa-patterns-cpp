/*
Problem: 1186. Maximum Subarray Sum with One Deletion
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/description/
Pattern: Kadanes
Difficulty: Medium
*/

#include <iostream>
using namespace std;

int maxSum(vector<int>&arr){
    int nodelete = arr[0];
    int onedelete = INT_MIN;
    int res = arr[0];
    for(int i=1;i<arr.size();i++){
        int prevNoDel = nodelete;
        nodelete = max(nodelete + arr[i],arr[i]);

        onedelete = max(onedelete == INT_MIN ? INT_MIN: onedelete + arr[i],prevNoDel);
        res = max(res,max(nodelete,onedelete));
    }
    return res;
}

int main(){
    vector<int>arr = {1,-2,-2,3};
    cout<<maxSum(arr);
}
