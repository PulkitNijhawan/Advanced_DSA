#include <iostream>
#include <vector>
using namespace std;
class Node
{
    int data;
    Node *left;
    Node *right;
    int height = 0;
    int bal = 0;
    Node(int d)
    {
        this->data = d;
    }
};
Node *construct(vector<int> &arr, int h, int l)
{
    if (l > h)
        return nullptr;
    int mid = (h + l) / 2;
    Node *n = new Node(arr[mid]);
    n->left = construct(arr, mid - 1, l);
    n->right = construct(arr, h, mid + 1);
    newHeight_Bal(n);
    return n;
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
void newHeight_Bal(Node *node)
{
    int lh = -1;
    int rh = -1;
    if (node->left != nullptr)
        lh = node->left->height;
    if (node->right != nullptr)
        rh = node->right->height;
    node->height = max(lh, rh) + 1;
    node->bal = lh - rh;
}
Node *LL(Node *A)
{
    Node *B = A->left;
    Node *Bsub = B->right;
    B->right = A;
    A->left = Bsub;
    newHeight_Bal(A);
    newHeight_Bal(B);
    return B;
}
Node *RR(Node *A)
{
    Node *B = A->right;
    Node *Bsub = B->left;
    B->left = A;
    A->right = Bsub;
    newHeight_Bal(A);
    newHeight_Bal(B);
    return B;
}
Node *tryRotate(Node *node)
{
    newHeight_Bal(node);
    if (node->bal == 2)
    {
        if (node->left->bal == 1)
        {
            node = LL(node);
            return node;
        }
        else
        {
            node->left = RR(node->left);
            node = LL(node);
            return node;
        }
    }
    else if (node->bal == -2)
    {
        if (node->right->bal == -1)
        {
            return RR(node);
        }
        else
        {
            node->right = LL(node->right);
            return RR(node);
        }
    }
}
Node *addNode(Node *root, int val)
{
    if (root == nullptr)
        return new Node(val);
    if (val < root->data)
        root->left = addNode(root->left, val);
    else if (val > root->data)
        root->right = addNode(root->right, val);
    return tryRotate(root);
}
Node *remove(Node *root, int val)
{
    if (val < root->data)
        root->left = remove(root->left, val);
    else if (val > root->data)
        root->right = remove(root->right, val);
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            return root->left == nullptr ? root->right : root->left;
        }
        else
        {
            int max = maxEle(root->left);
            root->data = max;
            root->left = remove(root->left, max);
        }
    }
    return tryRotate(root);
}
int main()
{
}