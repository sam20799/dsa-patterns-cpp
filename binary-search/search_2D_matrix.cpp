/*
Problem: 74. Search a 2D Matrix
Platform: LeetCode
Problem Link: https://leetcode.com/problems/search-a-2d-matrix/description/
Pattern: Binary Search
Difficulty: Medium
*/

#include <iostream>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();

    int low = 0;
    int high = n*m-1;

    while(low<=high){
        int guess = (low+high)/2;
        int row = guess/m;
        int col = guess%m;

        if(matrix[row][col] == target) return true;
        if(matrix[row][col]< target) low = guess+1;
        else high = guess-1;
    }
    return false;


}

int main(){
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;
    cout<<searchMatrix(matrix,target);
}