/*
Problem: 986. Interval List Intersections
Platform: LeetCode
Problem Link: https://leetcode.com/problems/interval-list-intersections/description/
Pattern: Merge Intevals
Difficulty: Medium
*/

#include <iostream>
using namespace std;

vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
    
        int n = firstList.size();
        int m = secondList.size();
        int i = 0;
        int j = 0;

        vector<vector<int>>res;

        while(i<n && j<m){
            int start1 = firstList[i][0];
            int end1 = firstList[i][1];
            int start2 = secondList[j][0];
            int end2 = secondList[j][1];
            if(start1 <= start2){ // if sorted
                if(end1 >= start2){ // finding overlap
                    int s = max(start1,start2);
                    int e = min(end1,end2);
                    res.push_back({s,e});
                }
            }
            else{
                if(end2 >= start1){   // if not sorted
                    int s = max(start1,start2);
                    int e = min(end1,end2);
                    res.push_back({s,e});
                }
            }
            if(end1<=end2){
                i++;
            }
            else j++;
        }
        return res;
    }



int main(){
    vector<vector<int>>firstList = {{0,2}, {5,10}, {13,23}, {24,25}};
    vector<vector<int>>secondList = {{1,5}, {8,12}, {15,24}, {25,26}};
    vector<vector<int>>res = intervalIntersection(firstList,secondList);
    for(auto x:res){
        cout<<"[ ";
        for(auto y: x){
            cout<<y<<" ";
        }
        cout<<"]";
    }

}