/*
Problem: 141. Linked List Cycle
Platform: LeetCode
Problem Link: https://leetcode.com/problems/linked-list-cycle/description/
Pattern: Linked List
Difficulty: Easy
*/

#include <iostream>
using namespace std;

struct ListNode{
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
        bool hasCycle(ListNode *head){
            if(head == nullptr) return false;
            if(head->next == nullptr) return false;
            ListNode *slow = head;
            ListNode *fast = head;
            while(fast != nullptr and fast->next != nullptr){
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast) return true;
            }
            return false;
        }
};


int main(){
    ListNode* head = new ListNode(3);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(0);
    ListNode* node4 = new ListNode(-4);

    //connect the nodes
    head->next = node2;
    node2->next = node3;
    node3->next = node4;

    //create cycle
    node4->next = node2;
    Solution solution;

    cout << solution.hasCycle(head) << endl;
}