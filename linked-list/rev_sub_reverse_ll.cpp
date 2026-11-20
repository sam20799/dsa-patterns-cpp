/*
Problem: 24. Swap Nodes in Pairs
Platform: LeetCode
Problem Link: https://leetcode.com/problems/swap-nodes-in-pairs/description/
Pattern: Linked List
Difficulty: Medium
*/


#include <iostream>
using namespace std;

class ListNode{
    public:
        int data;
        ListNode* next;
    ListNode(int data1){
        data = data1;
        next = nullptr;
    }
};

ListNode* reverseBetween(ListNode* head, int left, int right){
    int pos = 1;
    ListNode* temp = head;
    ListNode* before = nullptr;
    while(pos<left){
        before = temp;
        temp = temp->next;
        pos++;
    }

    ListNode* curr = temp;
    ListNode* prev = nullptr;
    int times = right-left+1;

    while(times--){
        ListNode* nex = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nex;
    }
    temp->next = curr;
    if(before){
        before->next = prev;
        return head;
    }
    return prev;

}

int main(){
    vector<int> arr = {1,2,3,4,5};
    ListNode* head = new ListNode(arr[0]);
    ListNode* node1 = new ListNode(arr[1]);
    ListNode* node2 = new ListNode(arr[2]);
    ListNode* node3 = new ListNode(arr[3]);
    ListNode* node4 = new ListNode(arr[4]);

    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    ListNode* curr = head;

    ListNode* prev = nullptr;

    while(curr!=nullptr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }
    cout<<endl;
    int left = 2;
    int right = 4;
    ListNode* newhead = reverseBetween(head,left,right);
    ListNode* new_curr = newhead;
    ListNode* new_prev = nullptr;

    while(new_curr != nullptr){
        cout<<new_curr->data<<" ";
        new_curr = new_curr->next;
    }



}