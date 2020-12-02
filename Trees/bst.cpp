#include <iostream>
#include <vector>
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
    Node()
    {
    }
};
vector<int> ans;
Node *construct(vector<int> &arr, int h, int l)
{
    if (l > h)
        return nullptr;
    int mid = (h + l) / 2;
    Node *n = new Node(arr[mid]);
    n->left = construct(arr, mid - 1, l);
    n->right = construct(arr, h, mid + 1);
    return n;
}
void display(Node *root)
{
    if (root == nullptr)
        return;
    string str = "";
    str += (root->left != nullptr ? to_string(root->data) : ".");
    str += " <- " + to_string(root->data) + " -> ";
    str += (root->right != nullptr ? to_string(root->data) : ".");
    display(root->left);
    display(root->right);
}
//==========================Basic============================================================
bool find01(Node *root, int k)
{
    Node *curr = root;
    while (curr != nullptr)
    {
        if (curr->data > k)
            curr = curr->left;
        else if (curr->data == k)
            return true;
        else
            curr = curr->right;
    }
    return false;
}
bool find02(Node *root, int k)
{
    if (root == nullptr)
        return false;
    if (root->data == k)
        return true;
    else if (root->data > k)
        return find02(root->left, k);
    else
        return find02(root->right, k);
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
int minEle(Node *root)
{
    Node *curr = root;
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr->data;
}
//=====================================Paths============================================================
void n2rp(Node *root, int val, vector<int> &path)
{
    if (root == nullptr)
        return;
    if (root.data == val)
    {
        path.push_back(val);
        return;
    }
    path.push_back(root->data);
    if (root->data > val)
        n2rp(root->left, val, path);
    else if (root->data < val)
        n2rp(root->right, val, path);
}
int LCA(Node *root, int a, int b)
{
    if (root == nullptr)
        return -1;
    if (root->data > a && root->data > b)
        return LCA(root->left, a, b);
    else if (root->data < a && root->data < b)
        return LCA(root->right, a, b);
    else
    {
        return root->data;
    }
}
void elementsA2B_01(Node *root, int a, int b)
{
    if (root == nullptr)
        return;
    elementsA2B_01(root->left, a, b);
    if (root->data > a && root->data < b)
    {
        ans.push_back(root->data); //sorted ans;
    }
    if (root->data > b)
        return;
    elementsA2B_01(root->right, a, b);
}
void elementsA2B_02(Node *root, int a, int b)
{
    if (root == nullptr)
        return;
    if (root->data >= a && root->data <= b)
        ans.push_back(root->data);
    if (a > root->data && b > root->data)
    {
        elementsA2B_02(root->right, a, b);
    }
    else if (a < root->data && b < root->data)
    {
        elementsA2B_02(root->left, a, b);
    }
    else
    {
        elementsA2B_02(root->left, a, b);
        elementsA2B_02(root->right, a, b);
    }
}
//==============================Pre-Succ============================================================
void preInBst(Node *root, int data)
{
    Node *curr = root;
    Node *pred = null;
    while (true)
    {
        if (curr->data == data)
        {
            if (curr->left == null)
            {
                cout << pred.data << endl;
            }
            else
            {
                pred = curr->left while (pred->right != nullptr)
                {
                    pred = pred->right;
                }
            }
            break;
        }
        else if (curr->data > data)
        {

            curr = curr->left;
        }
        else
        {
            pred = curr;
            curr = curr->right;
        }
    }
}
//===============================Preorder=============================================================
int idx = 0;
Node *constructBST(vector<int> &arr, int lb, int ub)
{
    if (arr[idx] < lb || arr[idx] > ub || idx == arr.size())
        return nullptr;
    Node *n = new Node(arr[idx++]);
    n->left = constructBST(arr, lb, node->data);
    n->right = constructBST(arr, node->data, ub);
    return n;
}
Node *addData01(Node *root, int val)
{
    if (root == nullptr)
        return new Node(val);
    if (root->data > val)
        root->left = addData01(root->left, val);
    if (root->data < val)
        root->right = addData01(root->right, val);
    return root;
}
Node *addDAta02(Node *root, int val)
{
    Node *curr = root;
    if (curr == nullptr)
    {
        return new Node(val);
    }
    Node *prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (curr->data > val)
        {
            curr = curr->left;
        }
        else if (curr->data < val)
        {
            curr = curr->right;
        }
    }
    if (prev->right == nullptr && prev->left == nullptr)
    {
        if (prev->data > val)
            prev->left = new Node(val);
        else
            prev->right = new Node(val);
    }
    else if (prev->right == nullptr)
        prev->right = new Node(val);
    else
        prev->left = new Node(val);
    return root;
}
Node *removeData(Node *root, int key)
{
    if (root == nullptr)
        return nullptr;
    if (root->data > key)
        root->left = removeData(root->left, key);
    else if (root->data < key)
        root->right = removeData(root->right, key);
    else
    {
        if (root->right == nullptr || root->left == nullptr)
        {
            return root->right != null ? root->right : root->left;
        }
        else
        {
            int maxEle = maxELe(root->left);
            root->data = maxEle;
            root->left = removeData(root->left, maxEle);
        }
    }
    return root;
}
int main()
{
    vector<int> arr{10, 20, 30, 40, 50, 60, 70, 80, 90};
    Node *root = construct(arr, arr.size() - 1, 0);
    cout << find02(root, 100);
}