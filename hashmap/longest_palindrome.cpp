/*
Problem: 409. Longest Palindrome
Platform: LeetCode
Problem Link: https://leetcode.com/problems/longest-palindrome/description/
Pattern: Hashmap
Difficulty: Easy
*/

#include <iostream>
using namespace std;

int longestPalindrome(string s) {
    unordered_map<char,int>f;

    for(int i=0;i<s.size();i++){
        f[s[i]]++;
    }

    int res = 0;
    bool odd = false;

    for(auto i: f){            // if even -> can be added
        int val = i.second;
        if(val%2 ==0){
            res += val;
        }
        else{
            odd = true;
        }  
    }
    if(odd == false) return res;     // if odd -> extract even
    for(auto i: f){
        int val = i.second;
        if(val%2 == 1){
            res += val-1;
        }
    }
    return res+1;                  // out of all singles from odd: add any one in middle
}

int main(){
    string s = "a";
    cout<<longestPalindrome(s);

}