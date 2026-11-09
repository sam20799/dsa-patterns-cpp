/*
Problem: 1480. Running Sum of 1d Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/running-sum-of-1d-array/description/
Pattern: Prefix Sum
Difficulty: Easy
*/

#include <iostream>
using namespace std;

vector<int> runningSum(vector<int>&arr){
    vector<int>pre(arr.size());
    pre[0] = arr[0];
    for(int i=1;i<arr.size();i++){
        pre[i] = pre[i-1] + arr[i];
    }
    return pre;
}

int main(){
    vector<int>arr = {3,1,2,10,1};
    vector<int>pre = runningSum(arr);
    for(auto i: pre){
        cout<<i<<" ";
    }
}