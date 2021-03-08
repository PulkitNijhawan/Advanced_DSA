#include <iostream>
#include <vector>
#include <list>
using namespace std;
#define mod 1000000007
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
template <typename T>
void print(vector<T> &dp)
{
    for (T i : dp)
        cout << i << " ";
    cout << "\n";
}
template <typename T>
void print2d(vector<vector<T>> &dp)
{
    for (vector<T> &arr : dp)
        print(arr);
    cout << "\n";
}

//=========================================================================================================================

int matrixChainMulti(vi &arr, int si, int ei, vvi &dp)
{
    if (si + 1 == ei)
        return dp[si][ei] = 0;
    if (dp[si][ei] != -1)
        return dp[si][ei];
    int tendency = (int)1e5;
    for (int cut = si + 1; cut < ei; cut++)
    {
        int leftTree = matrixChainMulti(arr, si, cut, dp);
        int rightTree = matrixChainMulti(arr, cut, ei, dp);
        int costOfMultiply = leftTree + rightTree + (arr[cut] * arr[si] * arr[ei]);
        tendency = min(tendency, costOfMultiply);
    }
    return dp[si][ei] = tendency;
}
int matrixChainMultiDp(vi &arr, int SI, int EI, vvi &dp)
{
    int n = arr.size();
    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; ei++, si++)
        {
            if (si + 1 == ei)
            {
                dp[si][ei] = 0;
                continue;
            }
            int tendency = (int)1e5;
            for (int cut = si + 1; cut < ei; cut++)
            {
                int leftTree = dp[si][cut];
                int rightTree = dp[cut][ei];
                int costOfMultiply = leftTree + rightTree + (arr[cut] * arr[si] * arr[ei]);
                tendency = min(tendency, costOfMultiply);
            }
            dp[si][ei] = tendency;
        }
    }
    return dp[SI][EI];
}
int matrixChainMultiPath(vi &arr, int SI, int EI, vvi &dp)
{
    int n = arr.size();
    vector<vector<string>> path(n, vector<string>(n, ""));
    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; ei++, si++)
        {
            if (si + 1 == ei)
            {
                dp[si][ei] = 0;
                string str = "";
                str.push_back((char)(si + 'A'));
                path[si][ei] = str;
                continue;
            }
            int tendency = (int)1e5;
            for (int cut = si + 1; cut < ei; cut++)
            {
                int leftTree = dp[si][cut];
                int rightTree = dp[cut][ei];
                int costOfMultiply = leftTree + rightTree + (arr[cut] * arr[si] * arr[ei]);
                if (costOfMultiply < tendency)
                {
                    tendency = costOfMultiply;
                    path[si][ei] = "(" + path[si][cut] + path[cut][ei] + ")";
                }
            }
            dp[si][ei] = tendency;
        }
    }
    print2d(path);

    return dp[SI][EI];
}
pii minMaxEval(vi &arr, vector<char> &op, int si, int ei, vector<vector<pii>> &dp)
{ //pair => first:min , second:max
    if (si == ei)
    {
        return dp[si][ei] = make_pair(arr[si], arr[si]);
    }
    if (dp[si][ei].first != 0 && dp[si][ei].second != 0)
        return dp[si][ei];
    pii tendency = make_pair(1e8, -1e8);
    for (int cut = si; cut < ei; cut++)
    {
        pii rightPair = minMaxEval(arr, op, si, cut, dp);
        pii leftPair = minMaxEval(arr, op, cut + 1, ei, dp);
        int maxVal = 0, minVal = 0;
        if (op[cut] == '*')
        {
            maxVal = rightPair.second * leftPair.second;
            minVal = rightPair.first * leftPair.first;
        }
        else
        {
            maxVal = rightPair.second + leftPair.second;
            minVal = rightPair.first + leftPair.first;
        }
        tendency.first = min(minVal, tendency.first);
        tendency.second = max(maxVal, tendency.second);
    }
    return dp[si][ei] = tendency;
}
int burstBalloons(vi &arr, int si, int ei, vvi &dp)
{
    int l = si == 0 ? 1 : arr[si - 1];
    int r = ei == arr.size() - 1 ? 1 : arr[ei + 1];
    if (dp[si][ei] != -1)
        return dp[si][ei];
    int tendency = -100;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftTree = cut == si ? 0 : burstBalloons(arr, si, cut - 1, dp);
        int rightTree = cut == ei ? 0 : burstBalloons(arr, cut + 1, ei, dp);
        int currCutVal = leftTree + rightTree + (arr[cut] * l * r);
        tendency = max(tendency, currCutVal);
    }
    return dp[si][ei] = tendency;
}
int optimalBST(vi &arr, vi &freq, int si, int ei, vi &prefixOBST, vvi &dp)
{
    if (dp[si][ei] != -1)
        return dp[si][ei];
    int tendency = 1e8;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftTree = cut == si ? 0 : optimalBST(arr, freq, si, cut - 1, prefixOBST, dp);
        int rightTree = cut == ei ? 0 : optimalBST(arr, freq, cut + 1, ei, prefixOBST, dp);
        tendency = min(tendency, leftTree + (prefixOBST[ei] - (si == 0 ? 0 : prefixOBST[si - 1])) + rightTree);
    }
    return dp[si][ei] = tendency;
}
int OBST_Dp(vi &arr, vi &freq,int SI,int EI, vi &prefixOBST, vvi &dp)
{
    int n = arr.size();
    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; ei++, si++)
        {
            int tendency = 1e8;
            for (int cut = si; cut <= ei; cut++)
            {
                int leftTree = cut == si ? 0 : dp[si][cut-1];
                int rightTree = cut == ei ? 0 : dp[cut+1][ei];
                tendency = min(tendency, leftTree + (prefixOBST[ei] - (si == 0 ? 0 : prefixOBST[si - 1])) + rightTree);
            }
            dp[si][ei] = tendency;
        }
    }
    return dp[SI][EI];
}
void OBST()
{
    vi arr{10, 12, 20};
    vi freq{34, 8, 50};
    int sum = 0;
    vi prefixOBST(arr.size());
    int idx = 0;
    for (int ele : freq)
    {
        sum += ele;
        prefixOBST[idx++] = sum;
    }
    int si = 0;
    int ei = arr.size() - 1;
    vvi dp(ei + 1, vi(ei + 1, -1));
    cout << OBST_Dp(arr, freq, si, ei, prefixOBST, dp) << "\n";
    print2d(dp);
}
void BB()
{
    vi arr{2, 1, 5, 8, 3};
    int si = 0;
    int ei = arr.size() - 1;
    vvi dp(ei + 1, vi(ei + 1, -1));
    cout << burstBalloons(arr, si, ei, dp) << "\n";
    print2d(dp);
}
void MINMAX()
{
    int si = 0;
    vi arr{1, 2, 3, 4, 5};
    int ei = arr.size() - 1;
    vector<char> op{'+', '*', '+', '*'};
    vector<vector<pii>> dp(ei + 1, vector<pii>(ei + 1, {0, 0}));
    cout << minMaxEval(arr, op, si, ei, dp).second << " " << minMaxEval(arr, op, si, ei, dp).first << "\n";
}
void MCM()
{
    vi arr{4, 2, 3, 1, 3};
    int si = 0, ei = arr.size() - 1;
    vvi dp(ei + 1, vi(ei + 1, 0));
    cout << matrixChainMultiPath(arr, si, ei, dp) << "\n";
    // print2d(dp);
}
void solve()
{
    // g++ cutType.cpp -o p&&./p > output.txt
    // MCM();
    // MINMAX();
    //BB();
    OBST();
}
int main()
{
    solve();
    return 0;
}