#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int k)
    {
        this->data = k;
    }
};
int idx = 0;
Node *constructTree(vector<int> &arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        idx++;
        return nullptr;
    }
    Node *root = new Node(arr[idx++]);
    root->left = constructTree(arr);
    root->right = constructTree(arr);
    return root;
}
void display(Node *root)
{
    if (root == nullptr)
        return;
    string str = "";
    str += ((root->left != nullptr) ? to_string(root->left->data) : ".");
    str += " <- " + to_string(root->data) + " -> ";
    str += ((root->right != nullptr) ? to_string(root->right->data) : ".");
    cout << str + '\n';
    display(root->left);
    display(root->right);
}
int main()
{
    vector<int> arr={10,20,40,-1,-1,50,-1,-1,30,60,100,-1,-1,-1,70,110,-1,-1,120,-1,-1};
    Node* root=constructTree(arr);
    display(root);
}