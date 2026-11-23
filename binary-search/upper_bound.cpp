/*
Problem: Ceil in Sorted Array
Platform: GFG
Problem Link: https://www.geeksforgeeks.org/problems/ceil-in-a-sorted-array/1
Pattern: Binary Search
Difficulty: Easy
*/


#include <iostream>
using namespace std;

int findCeil(vector<int>& arr,int x){
    int low = 0;
    int high = arr.size()-1;
    int ans = -1;

    while(low<=high){
        int mid = (low+high)/2;
        if(arr[mid]>=x){
            ans = mid;
            high = mid-1;
        }
        else low = mid+1;
    }
    return ans;
}

int main(){
    vector<int>arr = {1, 2, 8, 10, 11, 12, 19};
    int x = 5;
    cout<<findCeil(arr,x);

}