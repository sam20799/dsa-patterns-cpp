/*
Problem: 875. Koko Eating Bananas
Platform: LeetCode
Problem Link: https://leetcode.com/problems/koko-eating-bananas/description/
Pattern: Binary Search
Difficulty: Medium
*/



#include <iostream>
#include <algorithm>

using namespace std;

long long hour(vector<int>&arr,int n, int speed){
        long long h = 0;

        for(int i=0;i<n;i++){
            h += (arr[i]/speed);
            if(arr[i]%speed != 0) h++;
        }
        return h;
    }
int minEatingSpeed(vector<int>& piles, int h) {
    int n = piles.size();
    int low = 1;
    int high = *max_element(piles.begin(),piles.end());
    int res = -1;
    while(low<=high){
        int mid = (low+high)/2;  //speed
        long long hr = hour(piles,n,mid);

        if(hr>h) low = mid+1;
        else{
            res = mid;
            high = mid-1;
        }

    }
    return res;
}

int main(){
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    cout<<minEatingSpeed(piles,h);
}