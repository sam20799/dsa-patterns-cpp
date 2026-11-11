/*
Problem: Meeting Rooms II
Platform: GFG
Problem Link: https://www.geeksforgeeks.org/problems/attend-all-meetings-ii/1
Pattern: Merge Intevals
Difficulty: Medium
*/

#include <iostream>
using namespace std;
int minMeetingRooms(vector<int> &start, vector<int> &end) {
        sort(start.begin(),start.end());
        sort(end.begin(),end.end());
        int i=0,j=0;
        int room=0;
        int res=0;
        while(i<start.size()){
            if(start[i]<end[j]){
                room++;
                res = max(res,room);
                i++;
            }
            else{
                room--;
                j++;
            }
        }
        return res;
        
    }

int main(){
    vector<int>start = {2,9,6};
    vector<int>end = {4,12,10};
    cout<<minMeetingRooms(start,end);
}