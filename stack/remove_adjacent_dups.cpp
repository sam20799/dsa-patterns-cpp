/*
Problem: 1047. Remove All Adjacent Duplicates In String
Platform: LeetCode
Problem Link: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/description/
Pattern: Stack
Difficulty: Easy
*/

#include <iostream>
using namespace std;

string removeDuplicates(string s) {

    stack<char>st;
    st.push(s[0]);
    for(int i=1;i<s.size();i++){
        if(!st.empty() && s[i] == st.top()){
            st.pop();
            continue;
        }
        else{
            st.push(s[i]);
        }
    }
    string ans;
    while(!st.empty()){
        ans += st.top();
        st.pop();
    }
    reverse(ans.begin(),ans.end());
    return ans;

};

int main(){
    string s = "abbaca";
    string ans = removeDuplicates(s);
    cout<<ans;

}