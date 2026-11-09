/*
Problem: 56. Merge Intervals
Platform: LeetCode
Problem Link: https://leetcode.com/problems/merge-intervals/description/
Pattern: Merge Intevals
Difficulty: Medium
*/

#include <iostream>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        vector<vector<int>> res;
        int start1 = intervals[0][0];
        int end1 = intervals[0][1];

        for(int i=1;i<intervals.size();i++){
            int start2 = intervals[i][0];
            int end2 = intervals[i][1];

            if(end1 >= start2){
                start1 = min(start1,start2);
                end1 = max(end1,end2);
                continue;
            }
            res.push_back({start1,end1});
            start1 = start2;
            end1 = end2;
        }
        res.push_back({start1,end1});
        return res;
    }

int main(){
    vector<vector<int>> arr = {{1,3}, {2,6}, {8,10}, {15,18}};
    vector<vector<int>> res = merge(arr);
    for(auto x: res){
        cout<<"["<< x[0]<<","<< x[1]<< "] ";
    }

}