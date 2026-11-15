/*
Problem: 1209. Remove All Adjacent Duplicates in String II
Platform: LeetCode
Problem Link: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/description/
Pattern: Stack
Difficulty: Medium
*/

#include <iostream>
using namespace std;

string removeDuplicates(string s, int k) {
    int n = s.size();
    stack<pair<char,int>> st;
    for(int i=0;i<n;i++){
        char ch = s[i];
        if(st.empty()){
            st.push({ch,1});
            continue;
        }
        if(st.top().first != ch){
            st.push({ch,1});
            continue;
        }
        if(st.top().second < (k-1)){
            st.top().second += 1;
            continue;
        }
        st.pop();
    }

    string ans = "";
    while(!st.empty()){
        pair<char,int>p = st.top();
        st.pop();
        while(p.second --){
            ans += p.first;
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;


}


int main(){
    // stack<pair<char,int>>st;
    // st.push({'a',1});
    // st.top().second += 1;
    // cout<<st.top().first<<endl;
    // cout<<st.top().second;

    string s = "pbbcggttciiippooaais";
    int k = 2;
    cout<<removeDuplicates(s,k);
}