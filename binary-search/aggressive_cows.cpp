/*
Problem: Aggressive Cows
Platform: GFG
Problem Link: https://www.geeksforgeeks.org/problems/aggressive-cows/1
Pattern: Binary Search
Difficulty: Medium
*/

#include <iostream>
using namespace std;

bool fun(vector<int>&arr,int n,int k, int guess){
    int cow = 1;
    int pos = arr[0];
    for(int i=1;i<n;i++){
        int dist = arr[i]-pos;
        if(dist<guess) continue;
        cow ++;
        pos = arr[i];
    }
    if(cow>= k) return true;
    else return false;
}
int aggressiveCows(vector<int> &arr, int k) {
    // code here
    int n = arr.size();
    sort(arr.begin(),arr.end());
    
    int low = 1;
    int high = arr[n-1]-arr[0];
    int res = -1;
    while(low<=high){
        int guess = (low+high)/2;
        if(fun(arr,n,k,guess)){
            res = guess;
            low = guess+1;
        }
        else high = guess-1;
    }
    return res;
}


int main(){
    vector<int>arr = {1, 2, 4, 8, 9};
    int k = 3;

    cout<<aggressiveCows(arr,k);

}