/*
Problem: 206. Reverse Linked List
Platform: LeetCode
Problem Link: https://leetcode.com/problems/reverse-linked-list/description/
Pattern: Linked List
Difficulty: Easy
*/


#include <iostream>
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

ListNode* reverseList(ListNode* head){
    ListNode* curr = head;
    ListNode* prev = nullptr;

    while(curr != nullptr){
        ListNode* nex = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nex;
    }
    return prev;
}

int main(){
    vector<int>arr = {1,2,3,4,5};
    ListNode* head = new ListNode(arr[0]);
    ListNode* node2 = new ListNode(arr[1]);
    ListNode* node3 = new ListNode(arr[2]);
    ListNode* node4 = new ListNode(arr[3]);
    ListNode* node5 = new ListNode(arr[4]);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;


    ListNode* curr = head;
    while(curr!=nullptr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }

    cout<<endl;
    ListNode* newhead = reverseList(head);
    ListNode* curr1 = newhead;
    while(curr1 != nullptr){
        cout<<curr1->data<<" ";
        curr1 = curr1->next;
    }
}