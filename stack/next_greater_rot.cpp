/*
Problem: 503. Next Greater Element II
Platform: Leetcode
Problem Link: https://leetcode.com/problems/next-greater-element-ii/description/
Pattern: Stack
Difficulty: Medium
*/


#include <iostream>
using namespace std;

vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int>st;
        int n = nums.size();
        vector<int>res(n);

        for(int i=n-2;i>=0;i--){      //pushing all possible values in stack initially
            st.push(nums[i]);
        }

        for(int i=n-1;i>=0;i--){
            while(!st.empty() && st.top()<=nums[i]){
                st.pop();
            }
            if(st.empty()){
                res[i] = -1;
            }
            else{
                res[i] = st.top();
            }
            st.push(nums[i]);
        }
        return res;
}


int main(){
    vector<int> nums = {1, 2, 3, 4, 3};
    vector<int> res = nextGreaterElements(nums);
    for(auto x: res){
        cout<< x<<" ";
    }

}