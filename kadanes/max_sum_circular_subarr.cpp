/*
Problem: 918. Maximum Sum Circular Subarray
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-sum-circular-subarray/description/
Pattern: Kadanes
Difficulty: Medium
*/

#include <iostream>
using namespace std;


int maxSubCircular(vector<int>&arr){
    int maxending = arr[0];
    int minending = arr[0];
    int totalsum = arr[0];
    int maxsum = arr[0];
    int minsum = arr[0];
    for(int i=1;i<arr.size();i++){
        totalsum += arr[i];
        maxending = max(maxending + arr[i],arr[i]);
        maxsum = max(maxsum,maxending);
        minending = min(minending + arr[i],arr[i]);
        minsum = min(minsum,minending);
    }
    int circularsum = totalsum - minsum;
    if(maxsum < 0) return maxsum;  //maxsum < 0 -> mean we only have -ve items. (totalsum -min sum) == 0, max(-ve,0)->0 wrong ans
    return max(maxsum,circularsum);

}

int main(){
    vector<int> arr = {-3,-2,-3};
    cout<<maxSubCircular(arr);
}