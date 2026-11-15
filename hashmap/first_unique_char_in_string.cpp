/*
Problem: 387. First Unique Character in a String
Platform: LeetCode
Problem Link: https://leetcode.com/problems/first-unique-character-in-a-string/description/
Pattern: Hashmap
Difficulty: Easy
*/


#include <iostream>
using namespace std;

int firstUniqChar(string s) {
    int n = s.size();

    unordered_map<char,int> f;

    for(int i=0;i<n;i++){
        f[s[i]]++;
    }
    for(int i=0;i<n;i++){
        if(f[s[i]]==1){
            return i;
        }
    }
    return -1;
}

int main(){
    string s = "loveleetcode";
    cout<<firstUniqChar(s);
}