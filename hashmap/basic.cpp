/*
Problem: Basic
Platform: LeetCode
Problem Link: 
Pattern: Hashmap
Difficulty: 
*/



#include <iostream>
using namespace std;


int main(){
    unordered_map<int,int>f;
    f[1] = 10;
    f[3] = 5;
    f[2] = 4;

    for(auto i : f){
        int key = i.first;
        int value = i.second;

        cout<<key<<"->"<<value<<endl;
    }
    cout<<f[1]<<endl;
    if(f.find(5) == f.end()){
        //ture condition
        //cuz key is not there
    }
    if(f.find(1) != f.end()){
        //true condition
        //cuz key is there
    }
    cout<<endl;
    cout<<f.size();
    
}