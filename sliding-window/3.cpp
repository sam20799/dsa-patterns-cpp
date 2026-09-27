/*
Problem: 424. Longest Repeating Character Replacement
Platform: LeetCode
Problem Link: https://leetcode.com/problems/longest-repeating-character-replacement/description/
Pattern: Sliding Window
Difficulty: Medium
*/

#include <iostream>
using namespace std;
int max_cnt(vector<int>&arr){
    int max_count = INT_MIN;
    for(int i=0;i<arr.size();i++){
        if(arr[i]>max_count){
            max_count = arr[i];
        }
    }
    return max_count;
}

int charReplace(string s, int k){
    int n = s.size();
    int high;
    int low = 0;
    int res = 0;
    vector<int>char_cnt(256,0);
    for(high=0;high<n;high++){
        char_cnt[s[high]]++;
        int len = high-low+1;
        int max_count = max_cnt(char_cnt);
        int diff = len-max_count;

        while(diff>k){
            char_cnt[s[low]]--;
            low++;
            len = high-low+1;
            max_count = max_cnt(char_cnt);
            diff = len-max_count;
        }
        res = max(res,len);
    }
    return res;
}


int main(){
    string s;
    cin >> s;
    int k;
    cin>>k;
    cout<< charReplace(s,k);
    return 0;
}
