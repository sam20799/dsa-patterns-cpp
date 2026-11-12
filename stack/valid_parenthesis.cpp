/*
Problem: 20. Valid Parentheses
Platform: LeetCode
Problem Link: https://leetcode.com/problems/valid-parentheses/description/
Pattern: Stack
Difficulty: Easy
*/


#include <iostream>
using namespace std;

bool isValid(string s){
    stack<char>st;
    
    for(char ch: s){
        if(ch == '(' || ch == '{' ||  ch == '['){
            st.push(ch);
        }
        else{
            if(st.empty()) return false;  // if no opening

            if( ch == ')' && st.top() == '(' ||
                ch == '}' && st.top() == '{' ||
                ch == ']' && st.top() == '['){
                    st.pop();
                }
            else return false; // if top dont matches with ch "(])"
        }

    }
    return st.empty();

}

int main(){

    string s = "(])";
    cout<<isValid(s);

}