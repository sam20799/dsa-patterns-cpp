/*
Problem: 876. Middle of the Linked List
Platform: LeetCode
Problem Link: https://leetcode.com/problems/middle-of-the-linked-list/description/
Pattern: Linked List
Difficulty: Easy
*/
#include<iostream>
using namespace std;

class ListNode{
    public:
    int data;
    ListNode *next;

    ListNode(int data1){
        data = data1;
        next = nullptr;
    }
};

class Solution{
    public:
        ListNode *middleNode(ListNode *head){
            ListNode *slow = head;
            ListNode *fast = head;

            while(fast != nullptr and fast->next != nullptr){
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        }

};

int main(){
    vector<int>arr={1,2,3,4,5};
    //creating nodes
    ListNode *head = new ListNode(arr[0]);
    ListNode *node2 = new ListNode(arr[1]);
    ListNode *node3 = new ListNode(arr[2]);
    ListNode *node4 = new ListNode(arr[3]);
    ListNode *node5 = new ListNode(arr[4]);

    //connecting nodes
    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    Solution solution;
    ListNode *result = solution.middleNode(head);
    cout<<result->data;
}