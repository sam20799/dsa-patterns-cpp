/*
Problem: 53. Maximum Subarray
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-subarray/description/
Pattern: Kadanes
Difficulty: Medium
*/

#include <iostream>
using namespace std; 

class Solution{
    public:
        int maxSubArr(vector<int>& nums){
            int bestending = nums[0];
            int res = nums[0];
            for(int i=1;i<nums.size();i++){
                bestending = max(nums[i],bestending+nums[i]);
                res = max(res,bestending);
            }
            return res;
        }
};

int main(){
    int n;
    cin>>n;
    vector<int>arr ={5,4,-1,7,8};
    Solution solution;
    cout<<solution.maxSubArr(arr);
}
