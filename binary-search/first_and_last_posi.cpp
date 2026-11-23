/*
Problem: 34. Find First and Last Position of Element in Sorted Array
Platform: LeetCode
Problem Link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
Pattern: Binary Search
Difficulty: Medium
*/

#include <iostream>
using namespace std;


int findFirst(vector<int>arr,int x){
    int low = 0;
    int high = arr.size()-1;
    int ans = -1;
    while(low<=high){
        int mid = (low+high)/2;
        if(arr[mid]<x) low = mid+1;
        else if(arr[mid]>x) high = mid-1;
        else{ // ==x
            ans = mid;
            high = mid-1;
        }
    }
    return ans;
}

int findSecond(vector<int>arr,int x){
    int low = 0;
    int high = arr.size()-1;
    int ans = -1;
    while(low<=high){
        int mid = (low+high)/2;
        if(arr[mid]<x) low = mid+1;
        else if(arr[mid]>x) high = mid-1;
        else{ // ==x
            ans = mid;
            low = mid+1;
        }
    }
    return ans;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = findFirst(nums,target);
    int second = findSecond(nums,target);
    vector<int> ans;
    ans.push_back(first);
    ans.push_back(second);
    return ans;
}

int main(){
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    cout<<findFirst(nums,target);
    cout<<endl<<findSecond(nums,target);
    cout<<endl;

    vector<int>ans = searchRange(nums,target);

    for(auto x:ans){
        cout<<x<<" ";
    }

}