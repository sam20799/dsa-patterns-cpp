/*
Problem: 76. Minimum Window Substring
Platform: LeetCode
Problem Link: https://leetcode.com/problems/minimum-window-substring/description/?envType=study-plan-v2&envId=top-interview-150
Pattern: Sliding Window
Difficulty: Hard
*/

#include <iostream>
using namespace std;

bool sahi(vector<int>&have,vector<int>&need){
    for(int i=0;i<256;i++){
        if(have[i]<need[i]) {
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t){
    int low = 0, high = 0;
    int n = s.size();
    int m = t.size();
    int res = INT_MAX;
    int start = -1;
    vector<int> have(256,0);
    vector<int>need(256,0);

    for(int i=0;i<m;i++){
        need[t[i]]++;
    }

    for(high=0;high<n;high++){
        have[s[high]]++;
        while(sahi(have,need)){
            int len = high-low+1;
            if(res>len){
                res = len;
                start = low;
            }
            have[s[low]]--;
            low++;
        }
    }
    if(res==INT_MAX) return "";
    return s.substr(start,res);
  
}


int main(){
    string s, t;
    cin>>s;
    cin>>t;

    cout<<minWindow(s,t);
    return 0;
}
