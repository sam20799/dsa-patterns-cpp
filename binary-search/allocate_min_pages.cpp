/*
Problem: Allocate Minimum Pages
Platform: GFG
Problem Link: https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1
Pattern: Binary Search
Difficulty: Medium
*/


#include <iostream>
using namespace std;


bool isBookDistributed(vector<int>&arr,int n,long long limit,int k){
    int k_count = 1;
    long long page = 0;
    
    for(int i=0;i<n;i++){
        if(page+(long long)arr[i]<=limit){
            page += (long long)arr[i];
        }
        else{
            k_count++;
            page = (long long )arr[i];
            if(k_count>k){
                return false;
            }
        }
    }
    return true;
}
int findPages(vector<int> &arr, int k) {
    // code here
    int n = arr.size();
    if(n<k) return -1;
    long long low = 0;
    long long high = 0;
    long long res = -1;
    for(int i=0;i<n;i++){
        low = max(low,(long long)arr[i]);
        high += (long long)arr[i];
    }
    
    while(low<=high){
        long long guess = (low+high)/2;
        if(isBookDistributed(arr,n,guess,k)){
            res = guess;
            high = guess-1;
        }
        else low = guess+1;
        
    }
    return res;
}

int main(){
    vector<int> arr = {15, 17, 20};
    int k = 5;

    cout<<findPages(arr,k);
}