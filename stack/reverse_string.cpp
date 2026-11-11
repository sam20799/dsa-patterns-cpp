/*
Problem: 344. Reverse String
Platform: LeetCode
Problem Link: https://leetcode.com/problems/reverse-string/description/
Pattern: Stack
Difficulty: Easy
*/


#include <iostream>
using namespace std;

void reverseString(vector<char> &s){
    stack<char>st;

    for(char ch: s){
        st.push(ch);
    }

    for(int i=0;i<s.size();i++){
        s[i] = st.top();
        st.pop();
    }
}

int main(){
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    reverseString(s);
    for(char ch: s){
        cout<<ch;
    }
}