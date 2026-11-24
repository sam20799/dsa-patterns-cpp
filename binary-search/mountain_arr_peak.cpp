/*
Problem: 852. Peak Index in a Mountain Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/peak-index-in-a-mountain-array/description/
Pattern: Binary Search
Difficulty: Medium
*/

#include<iostream>
using namespace std;

int peakIndexInMountainArray(vector<int>& arr){
    int low = 0;
    int high = arr.size()-1;
    int res = 0;
    while(low<=high){
        int mid = (low+high)/2;
        if(arr[mid]<arr[mid+1]) low = mid+1;
        else{
            res = mid;
            high = mid-1;
        }
    }
    return res;
}

//arr[mid]<arr[mid+1] ->climbing, 
//arr[mid]>arr[mid+1]-> descending (a possible ans) find first occurance

int main(){
    vector<int> arr = {0, 2, 1, 0};
    cout<<peakIndexInMountainArray(arr);
}