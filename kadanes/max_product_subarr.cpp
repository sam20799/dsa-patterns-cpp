/*
Problem: 152. Maximum Product Subarray
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-product-subarray/description/
Pattern: Kadanes
Difficulty: Medium
*/

#include<iostream>
using namespace std;

int maxProduct(vector<int>&arr){
    int maxending = arr[0];
    int minending = arr[0];
    int res = arr[0];
    for(int i=1;i<arr.size();i++){
        int v1 = arr[i];
        int v2 = maxending*arr[i];
        int v3 = minending * arr[i];

        maxending = max(v1,max(v2,v3));
        minending = min(v1,min(v2,v3));

        res = max(res,maxending);

    }
    return res;
}

int main(){
    vector<int>arr = {2,3,-2,4};
    cout<<maxProduct(arr);
}