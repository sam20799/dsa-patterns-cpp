/*
Problem: 1749. Maximum Absolute Sum of Any Subarray
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/
Pattern: Kadanes
Difficulty: Medium
*/

#include <iostream>
using namespace std;

int maxSum(vector<int>&arr){
    int bestending = arr[0];
    int res = 0;
    for(int i=1;i<arr.size();i++){
        bestending = max(bestending + arr[i],arr[i]);
        res = max(res,bestending);
    }
    return res;
}

int minSum(vector<int>&arr){
    int bestending = arr[0];
    int res = 0;
    for(int i=1;i<arr.size();i++){
        bestending = min(bestending + arr[i],arr[i]);
        res = min(res,bestending);
    }
    return res;
}


int maxAbsSum(vector<int>&arr){
    int max1 = maxSum(arr);
    int max2 = abs(minSum(arr));
    return max(max1,max2);
}

int check(vector<int>&arr){
    int maxending = arr[0];
    int minending = arr[0];
    int res = abs(arr[0]);
    for(int i=1;i<arr.size();i++){
        maxending = max(maxending + arr[i],arr[i]);
        minending = min(minending + arr[i],arr[i]);
        res = max(res,max(abs(maxending),abs(minending)));
    }
    return res;
}
int main(){
    vector<int>arr = {-1};
    cout<<check(arr);
}