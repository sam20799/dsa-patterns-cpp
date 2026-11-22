/*
Problem: 61. Rotate List
Platform: LeetCode
Problem Link: https://leetcode.com/problems/rotate-list/description/
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

void print(ListNode* head){
    ListNode* curr = head;
    while(curr!= nullptr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }
}

ListNode* rotateRight(ListNode* head, int k) {
    if(head == nullptr) return nullptr;
    ListNode* last = head;
    int n =1;    // find total nodes
    while(last->next != nullptr){
        n++;
        last = last->next;
    }

    k = k%n;
    if(k==0) return head;   //rotate n times becomes given list

    ListNode* temp = head; // placing temp at pos n-k
    int count = 1;
    while(temp!=nullptr){
        if(count==(n-k)) break;
        count++;
        temp = temp->next;
    }
    
    // final adjustment

    last->next = head;
    ListNode* res = temp->next;
    temp->next = nullptr;
    return res;
        
}


int main(){
    vector<int>arr = {1,2,3,4,5};

    ListNode* head = new ListNode(arr[0]);
    ListNode* node1 = new ListNode(arr[1]);
    ListNode* node2 = new ListNode(arr[2]);
    ListNode* node3 = new ListNode(arr[3]);
    ListNode* node4 = new ListNode(arr[4]);

    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;


    print(head);
    cout<<endl;

    int k = 2;
    ListNode* newhead = rotateRight(head,k);
    print(newhead);
}
