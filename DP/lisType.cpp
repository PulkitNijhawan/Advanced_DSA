#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
#define mod 1000000007
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
void print(vector<int> &dp)
{
    for (int i : dp)
        cout << i << " ";
    cout << "\n";
}
void print2d(vector<vector<int>> &dp)
{
    for (vector<int> &arr : dp)
        print(arr);
    cout << "\n";
}
vi data{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
//=====================================================================================================================================//

int lis(int idx, vi &dp)
{
    if (dp[idx] != 0)
        return dp[idx];
    int tendency = 1;
    for (int i = idx - 1; i >= 0; i--)
    {
        if (data[idx] > data[i])
            tendency = max(tendency, lis(i, dp) + 1);
    }
    return dp[idx] = tendency;
}
int lisDp(vi &dp)
{
    int n = data.size();
    for (int idx = 0; idx < n; idx++)
    {
        int tendency = 1;
        for (int i = idx - 1; i >= 0; i--)
        {
            if (data[idx] > data[i])
                tendency = max(tendency, dp[i] + 1);
        }
        dp[idx] = tendency;
    }
    int ans = -1;
    for (int ele : dp)
        ans = max(ans, ele);
    return ans;
}
int lis_btr(vi &dp)
{
    int n = data.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
            if (data[i] > data[j])
                dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
    }
    return ans;
}
int lds(vi &dp)
{
    int n = dp.size();
    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = 1;
        for (int j = i + 1; j < n; j++)
            if (data[i] > data[j])
                dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
    }
    return ans;
}
int longestIncSumSubseq(vi &dp)
{
    int n = data.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = data[i];
        for (int j = i - 1; j >= 0; j--)
            if (data[i] > data[j]) //inc condition
                dp[i] = max(dp[i], dp[j] + data[i]);
        ans = max(ans, dp[i]);
    }
    return ans;
}
int sortedArrDeletion(vi &dp)
{
    int n = data.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; i >= 0; i--)
        {
            if (data[i] >= data[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(dp[i], ans);
    }
    return n - ans;
}
int russianDoll(vvi &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    int ans = 1;
    sort(arr.begin(), arr.end(), [](auto &a, auto &b) {
        if (a[0] == b[0])
            return a[1] > b[1];
        return a[0] < b[0];
    });
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i][1] > arr[j][1])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans; 
}
void RUSSDOLL()
{
    vvi arr{{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    cout << russianDoll(arr) << "\n";
}
void LISS()
{
    int n = data.size();
    vi dp(n, 0);
    longestIncSumSubseq(dp);
}
void LIS()
{

    int n = data.size();
    vi dp(n, 0);
    // lis( n - 1, dp);
    // lisDp(dp);
    cout << lis_btr(dp) << "\n";

    // int ans = -1;
    // for (int ele : dp)
    //     ans = max(ans, ele);
    print(dp);
}
void LDS()
{
    int n = data.size();
    vi dp(n, 0);
    cout << lds(dp) << "\n";
    print(dp);
}
void LBS()
{
    int n = data.size();
    vi dplis(n, 0);
    vi dplds(n, 0);
    lis_btr(dplis);
    lds(dplds);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, dplds[i] + dplis[i] - 1);
    }
    print(dplds);
    print(dplis);
    cout << ans << "\n";
}
void lisSet()
{
    // g++ lisType.cpp -o p&&./p > output.txt
    // LIS();
    // LDS();
    // LBS();
    // LISS();
    RUSSDOLL();
}
int main()
{
    
    lisSet();
    return 0;
}