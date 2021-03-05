#include <iostream>
#include <vector>
#include <list>
using namespace std;
#define mod 1000000007
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
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
void MCM()
{
    vi arr{4, 2, 3, 1, 3};
    int si = 0, ei = arr.size() - 1;
    vvi dp(ei + 1, vi(ei + 1, -1));
    cout << matrixChainMultiPath(arr, si, ei, dp) << "\n";
    print2d(dp);
}
void solve()
{
    // g++ cutType.cpp -o p&&./p > output.txt
    MCM();
}
int main()
{
    solve();
    return 0;
}