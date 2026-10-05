/*
Problem: 142. Linked List Cycle II
Platform: LeetCode
Problem Link: https://leetcode.com/problems/linked-list-cycle-ii/description/
Pattern: Linked List
Difficulty: Medium
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

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;

        while(fast!=nullptr and fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                slow = head;
                while(slow != fast){
                    slow = slow->next;
                    fast = fast->next;  
                }
                return fast;
            }

        }
        return nullptr;
    }
};



int main(){
    vector<int>arr={2,4,6,8,10};
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

    //creating cycle
    node5->next = node2;

    Solution solution;
    ListNode *result = solution.detectCycle(head);

    cout<<result->data;

    return 0;
}