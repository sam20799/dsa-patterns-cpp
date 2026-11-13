/*
Problem: Previous Greater
Platform: 
Problem Link: 
Pattern: Stack
Difficulty: Medium
*/


#include <iostream>
using namespace std;

vector<int>prevGreater(vector<int>& arr){
    int n = arr.size();
    vector<int>res(n);
    stack<int>st;
    res[0] = -1;
    st.push(arr[0]);

    for(int i=1;i<n;i++){
        while(!st.empty() && st.top()<=arr[i]){
            st.pop();
        }
        if(st.empty()){      // if stack is empty means no prev greater found
            res[i] = -1;
        }
        else{
            res[i] = st.top();
        }
        st.push(arr[i]);     // if stack is empty means current element is greater so still push it.

    }
    return res;

}


int main(){
    vector<int>arr = {4,1,2,5,3};
    vector<int>ans = prevGreater(arr);
    for(auto x : ans){
        cout<< x<< " ";
    }
}