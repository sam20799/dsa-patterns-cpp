/*
Problem: 202. Happy Number
Platform: LeetCode
Problem Link: https://leetcode.com/problems/happy-number/description/
Pattern: Linked List
Difficulty: Easy
*/

#include<iostream>
using namespace std;

class Solution {
public:
    int fun(int n){
        int sum = 0;
        while(n>0){
            int d = n%10;
            n = n/10;
            sum += d*d;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n;
        int fast = n;
        while(fast!=1){
            slow = fun(slow);
            fast = fun(fast);
            fast = fun(fast);
            if(slow == fast and slow != 1) return false;
        }
        return true;
    }
};

int main(){
    int n;
    cin>>n;
    Solution solution;
    cout<<solution.isHappy(n);
}