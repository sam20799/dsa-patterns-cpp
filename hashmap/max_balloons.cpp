/*
Problem: 1189. Maximum Number of Balloons
Platform: LeetCode
Problem Link: https://leetcode.com/problems/maximum-number-of-balloons/description/
Pattern: Hashmap
Difficulty: Easy
*/

#include <iostream>
using namespace std;

int maxNumberOfBalloons(string text) {
    string balloon = "balloon";
    unordered_map<char,int>have;
    unordered_map<char,int>need;
    for(int i=0;i<text.size();i++){
        have[text[i]]++;
    }
    for(int i=0;i<balloon.size();i++){
        need[balloon[i]]++;
    }
    int res = INT_MAX;
    for(auto i: need){
        char ch = i.first;
        int f_need = i.second;
        int f_have = have[ch];
        int times = f_have/f_need;
        res = min(res,times);
    }
    return res;

}

int main(){
    string text = "loonbalxballpoon";
    cout<<maxNumberOfBalloons(text);

}