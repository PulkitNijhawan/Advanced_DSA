#include<iostream>
#include<vector>
using namespace std;
class Stack{
    int tos=-1;
    int sz=0;
    int* arr;
    int N=1000;
public:
    Stack(){
        arr=new int[N]; 
    }
    Stack(int size){
        arr=new int[size];
        N=size;
    }
    void push(int d){
        if(tos==N-1)return;
        tos++;
        sz++;
        arr[tos]=d;
    }
    int pop(){
        if(tos==-1)return -1;
        tos--;
        sz--;
        return arr[tos+1];
    }
    bool isEmpty(){
        return sz==0;
    }
    int top(){
        if(sz==0)return -1;
        return arr[tos];
    }
    void clear(){
        tos=-1;
        sz=0;
        delete[] arr;
    }
    ~Stack(){
        delete arr;
    }
};
int main(){
    Stack st;
    for(int i=0;i<=5;i++)st.push(i);
    while(!st.isEmpty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}