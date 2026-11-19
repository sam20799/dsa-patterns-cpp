/*
Problem: 92. Reverse Linked List II
Platform: LeetCode
Problem Link: https://leetcode.com/problems/reverse-linked-list-ii/description/
Pattern: Linked List
Difficulty: Medium
*/

#include<iostream>
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


ListNode* reverseBetween(ListNode* head, int left, int right) {
    if(head == nullptr) return nullptr;
    if(left == right ) return head;

    ListNode* temp = head;
    ListNode* before = nullptr;
    int pos = 1;
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
    int left = 2;
    int right = 4;
    while(curr!=nullptr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }

    cout <<endl<< "after reverse: "<<endl;
    ListNode* newhead = reverseBetween(head,left,right);
    
    ListNode* newcurr = newhead;
    while(newcurr != nullptr){
        cout<<newcurr->data<<" ";
        newcurr = newcurr->next;
    }
}

