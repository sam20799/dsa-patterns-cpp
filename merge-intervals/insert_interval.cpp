/*
Problem: 57. Insert Interval
Platform: LeetCode
Problem Link: https://leetcode.com/problems/insert-interval/description/
Pattern: Merge Intevals
Difficulty: Medium
*/

#include <iostream>
using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back({newInterval[0],newInterval[1]});
        sort(intervals.begin(),intervals.end());
        int start1 = intervals[0][0];
        int end1 = intervals[0][1];
        vector<vector<int>>res;

        for(int i=1;i<intervals.size();i++){
            int start2 = intervals[i][0];
            int end2 = intervals[i][1];

            if(end1 >= start2){
                start1 = start1;
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
    vector<vector<int>> arr = {{1,3},{6,9}};
    vector<int>newInterval = {2,5};
    vector<vector<int>> res = insert(arr,newInterval);
    for(auto x: res){
        cout<<"["<< x[0]<<","<< x[1]<< "] ";
    }

}