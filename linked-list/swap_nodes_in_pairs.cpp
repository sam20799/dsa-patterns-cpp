/*
Problem: 24. Swap Nodes in Pairs
Platform: LeetCode
Problem Link: https://leetcode.com/problems/swap-nodes-in-pairs/description/
Pattern: Linked List
Difficulty: Medium
*/


#include <iostream>
using namespace std;



class Node{
    public:
        int data;
        Node* next;
    Node(int data1){
        data = data1;
        next = nullptr;
    }
};

void reverse(Node* head,int times){
    Node* curr = head;
    Node* prev = nullptr;

    while(times--){
        Node* nex = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nex;
    }
}

void print(Node* head){
    Node* curr = head;
    while(curr!= nullptr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }
}
Node* swapPairs(Node* head){
    if(head == nullptr) return nullptr;
    Node* left = head;
    Node* right;
    Node* prevleft = nullptr;
    Node* res = nullptr;
    int size = 2;
    // finding right
    while(true){

        right = left;
        for(int i=0;i<size-1;i++){
            if(right == nullptr) break;   // no right
            right = right->next;
        }
    
        if(right){ // if we have a right go like normal case
            Node* nextleft = right->next;
            reverse(left,size);
            if(prevleft){
                prevleft->next = right;
            }
            prevleft = left;
            if(res == nullptr){
                res = right;
            }
            left = nextleft;
    
        }
        else{
            if(prevleft){
                prevleft->next = left;
            }
            if(res == nullptr) res = left;
            break;
        }
    }
    return res;
    
}


int main(){

    vector<int>arr = {1,2,3,4};

    Node* head = new Node(arr[0]);
    Node* node1 = new Node(arr[1]);
    Node* node2 = new Node(arr[2]);
    Node* node3 = new Node(arr[3]);

    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    
    print(head);
    cout<<endl;
    Node* newhead = swapPairs(head);
    print(newhead);


}