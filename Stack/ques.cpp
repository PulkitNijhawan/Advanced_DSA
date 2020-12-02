#include<bits/stdc++.h>
using namespace std;

void ngl2r(vector<int>& arr,vector<int>& ans){
    stack<int> st;
    for(int i=0;i<arr.size();i++){
        while(!st.empty()&&arr[i]>arr[st.top()]){
            
            ans[st.top()]=arr[i];
            st.pop();
        }
        st.push(i);
    }
}
int main(){
    vector<int> arr{2,-1,8,6,9,4,3,5};
    vector<int> ans(arr.size());
    ngl2r(arr,ans);
    for(int i:ans)cout<<i<<" ";
}