/*
Problem: 383. Ransom Note
Platform: LeetCode
Problem Link: https://leetcode.com/problems/ransom-note/description/
Pattern: Hashmap
Difficulty: Easy
*/

#include <iostream>
using namespace std;

bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char,int>have;
    unordered_map<char,int>need;

    for(int i=0;i<ransomNote.size();i++){
        need[ransomNote[i]]++;
    }
    for(int i=0;i<magazine.size();i++){
        have[magazine[i]]++;
    }

    for(auto i: need){
        char ch = i.first;
        int f_need = i.second;
        int f_have = have[ch];

        if(f_have<f_need) return false;
        
    }
    return true;
}

int main(){
    string ransomNote = "aa";
    string magazine = "aab";
    cout<<canConstruct(ransomNote,magazine);

}