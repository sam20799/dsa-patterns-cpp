/*
Problem: Overlapping Intervals
Platform: GFG
Problem Link: https://www.geeksforgeeks.org/problems/overlapping-intervals--174556/1
Pattern: Merge Intevals
Difficulty: Easy
*/


#include <iostream>
using namespace std;

bool isIntersect(vector<vector<int>> intervals) {
    
    sort(intervals.begin(),intervals.end());
    int start1 = intervals[0][0];
    int end1 = intervals[0][1];
    
    for(int i=1;i<intervals.size();i++){
        int start2 = intervals[i][0];
        int end2 = intervals[i][1];
        
        if(end1>=start2) return true;
        start1 = start1;
        end1 = max(end1,end2);
    }
    return false;
}

int main(){
    vector<vector<int>> intervals = {{1, 3}, {5, 7}, {2, 4}, {6, 8}};
    cout<<isIntersect(intervals);
}