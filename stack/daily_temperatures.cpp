/*
Problem: 739. Daily Temperatures
Platform: Leetcode
Problem Link: https://leetcode.com/problems/daily-temperatures/description/
Pattern: Stack
Difficulty: Medium
*/

#include <iostream>
using namespace std;


vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int>res(n);
    stack<int>st;
    res[n-1] = 0;
    st.push(n-1); 
    for(int i=n-2;i>=0;i--){
        while(!st.empty() && temperatures[st.top()]<=temperatures[i]){
            st.pop();
        }
        if(st.empty()){
            res[i] = 0;
        }
        else{
            res[i] = st.top()-i;
        }
        st.push(i);
    }
    return res;
}
int main(){
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> res = dailyTemperatures(temperatures);
    for(auto x: res){
        cout<<x<<" ";
    }

}