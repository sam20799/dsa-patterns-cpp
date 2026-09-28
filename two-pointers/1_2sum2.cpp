/*
Problem: 424. Longest Repeating Character Replacement
Platform: LeetCode
Problem Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
Pattern: Two Pointers
Difficulty: Medium
*/

#include <iostream>
using namespace std;

pair<int, int> twosum(vector<int>& arr, int target){
    
    sort(arr.begin(),arr.end());
    int i = 0, j=arr.size()-1;
    while(i< j){
        int sum = arr[i] + arr[j];
        if (sum == target ) return {arr[i],arr[j]};
        else if (sum < target) i++;
        else j--;
    }
    return {-1, -1};
}

int main(){
    vector <int> arr;
    int n;
    cin >>n ;
    for(int i=0;i<n;i++){
        int x; 
        cin>> x;
        arr.push_back(x);
    }
    cout<< arr.size()<< endl;
    for(auto x: arr){
        cout<< x << " ";
    }
    cout<< endl;

    // 
    int target = 9;
    pair<int,int> result = twosum(arr,target);
    cout<<result.first<<" "<<result.second;

}