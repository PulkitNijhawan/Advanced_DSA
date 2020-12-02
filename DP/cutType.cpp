#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;
void display(vector<int> &arr)
{
    for (int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}
//=================================cutSet==============================================================
int mcmMemo(vector<int> &costs, int si, int ei, vector<vector<int>> &dp)
{
    if ((ei - si) == 1)
        return dp[si][ei] = 0;
    if (dp[si][ei] != -1)
        return dp[si][ei];
    int myAns = INT_MAX;
    for (int cut = si + 1; cut < ei; cut++)
    {
        int leftAns = mcmMemo(costs, si, cut, dp);
        int rightAns = mcmMemo(costs, cut, ei, dp);
        myAns = min(myAns, leftAns + rightAns + (costs[si] * costs[cut] * costs[ei]));
    }
    return dp[si][ei] = myAns;
}
int mcmDP(vector<int> &costs, vector<vector<int>> &dp)
{
    vector<vector<string>> sdp(dp.size(), vector<string>(dp.size(), ""));
    for (int gap = 1; gap < dp.size(); gap++)
    {
        for (int si = 0, ei = gap; ei < dp.size(); si++, ei++)
        {
            if ((ei - si) == 1)
            {
                dp[si][ei] = 0;
                sdp[si][ei] = (char)(si + 'A');
                continue;
            }
            int myAns = INT_MAX;
            string str = "";
            for (int cut = si + 1; cut < ei; cut++)
            {
                int leftAns = dp[si][cut];
                int rightAns = dp[cut][ei];
                int ans = leftAns + rightAns + (costs[si] * costs[cut] * costs[ei]);
                if (ans < myAns)
                {
                    myAns = ans;
                    str = "(" + sdp[si][cut] + sdp[cut][ei] + ")";
                }
            }
            dp[si][ei] = myAns;
            sdp[si][ei] = str;
        }
    }
    cout << sdp[0][dp.size() - 1] << endl;
    return dp[0][dp.size() - 1];
}
int searchCost(vector<int> &freq, int si, int ei)
{
    int sum = 0;
    for (int i = si; i <= ei; i++)
    {
        sum += freq[i];
    }
    return sum;
}
int obstMemo(vector<int> &freq, int si, int ei, vector<vector<int>> &dp)
{
    if (dp[si][ei] != -1)
        return dp[si][ei];
    int myAns = INT_MAX;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftAns = (cut == si) ? 0 : obstMemo(freq, si, cut - 1, dp);
        int rightAns = (cut == ei) ? 0 : obstMemo(freq, cut + 1, ei, dp);
        int ans = leftAns + searchCost(freq, si, ei) + rightAns;
        if (myAns > ans)
        {
            myAns = ans;
        }
    }
    return dp[si][ei] = myAns;
}
int obstDP(vector<int> &freq, vector<vector<int>> &dp)
{
    vector<int> prefixSum(freq.size(), 0);
    for (int i = 0; i < prefixSum.size(); i++)
    {
        prefixSum[i] = ((i == 0) ? 0 : prefixSum[i - 1]) + freq[i];
    }

    for (int gap = 0; gap < dp.size(); gap++)
    {
        for (int si = 0, ei = gap; ei < dp.size(); si++, ei++)
        {
            int myAns = INT_MAX;
            for (int cut = si; cut <= ei; cut++)
            {
                int leftAns = (cut == si) ? 0 : dp[si][cut - 1];
                int rightAns = (cut == ei) ? 0 : dp[cut + 1][ei];
                int ans = leftAns + (prefixSum[ei] - prefixSum[si] + freq[si]) + rightAns;
                if (myAns > ans)
                {
                    myAns = ans;
                }
            }
            dp[si][ei] = myAns;
        }
    }
    return dp[0][dp.size() - 1];
}
//=================================Utils===============================================================
void solve()
{
    vector<int> freq{34,8,50};
    int n = freq.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << obstDP(freq, dp) << endl;
    display2D(dp);
}
int main()
{
    solve();
}