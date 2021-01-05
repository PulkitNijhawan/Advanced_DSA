#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int d)
    {
        this->data = d;
    }
};
Node *constructTree(vector<int> &arr, int si, int ei)
{
    if (si > ei)
        return nullptr;
    int idx = (si + ei) >> 1;
    Node *node = new Node(arr[idx]);
    node->left = constructTree(arr, si, idx - 1);
    node->right = constructTree(arr, idx + 1, ei);
    return node;
}
void display(Node *root)
{
    if (root == nullptr)
        return;
    string str = "";
    str += root->left != nullptr ? to_string(root->left->data) : ".";
    str += " <- " + to_string(root->data) + " -> ";
    str += root->right != nullptr ? to_string(root->right->data) : ".";
    cout << str << "\n";
    display(root->left);
    display(root->right);
}
int size(Node *root)
{
    if (root == nullptr)
        return 0;
    return size(root->left) + size(root->right) + 1;
}
int height(Node *root)
{
    if (root == nullptr)
        return -1;
    return max(height(root->left), height(root->right)) + 1;
}
bool find(Node *root, int data)
{
    Node *curr = root;
    while (curr != nullptr)
    {
        if (curr->data == data)
            return true;
        else if (curr->data < data)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return false;
}
int maxEle(Node *root)
{
    Node *curr = root;
    while (curr->right != nullptr)
    {
        curr = curr->right;
    }
    return curr->data;
}
vector<Node *> n2rp_(Node *root, int d)
{
    vector<Node *> ans;
    Node *curr = root;
    while (curr != nullptr)
    {
        ans.push_back(curr);
        if (curr->data < d)
            curr = curr->right;
        else if (curr->data == d)
            break;
        else
            curr = curr->left;
    }
    return ans;
}
Node *lca(Node *root, int a, int b)
{
    vector<Node *> one = n2rp_(root, a);
    vector<Node *> two = n2rp_(root, b);
    int i = 0, j = 0;
    Node *ans = nullptr;
    while (i != one.size() && j != two.size())
    {
        if (one[i]->data != two[j]->data)
            break;
        ans = one[i];
        i++;
        j++;
    }
    return ans;
}
Node *lca02(Node *root, int a, int b)
{
    if (root == nullptr)
        return nullptr;
    if (root->data >= a && root->data <= b)
    {
        return root;
    }
    else if (root->data > a)
        return lca02(root->left, a, b);
    else
        return lca02(root->right, a, b);
}
Node *lca03(Node *root, int a, int b)
{
    Node *curr = root;
    while (curr != nullptr)
    {
        if (curr->data >= a && curr->data <= b)
        {
            return curr;
        }
        else if (curr->data > b)
            curr = curr->left;
        else
            curr = curr->right;
    }
}
void btwAnB01(Node *root, int a, int b, vector<Node *> &ans)
{
    if (root == nullptr)
        return;
    btwAnB01(root->left, a, b, ans);
    if (root->data >= a && root->data <= b)
        ans.push_back(root);
    if (root->data > b)
        return;
    btwAnB01(root->right, a, b, ans);
}
void btwAnB02(Node *root, int a, int b, vector<Node *> &ans){
    if(root==nullptr)return;
    if(root->data>b)btwAnB02(root->left, a, b, ans);
    else if(root->data<a)btwAnB02(root->right, a, b, ans);
    else{
        btwAnB02(root->left, a, b, ans);
        ans.push_back(root);
        btwAnB02(root->right, a, b, ans);
    }
}
int main()
{
    vector<int> arr{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
    Node *root = constructTree(arr, 0, arr.size() - 1);
    // cout<<maxEle(root);
    // vector<Node*> n2rp=n2rp_(root,110);
    // for(auto x:n2rp)cout<<x->data<<" ";
    // lca02(root,30,90);
    // cout<<lcaNode->data;
    vector<Node *> ans;
    btwAnB01(root, 10, 55, ans);
}