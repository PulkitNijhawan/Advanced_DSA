#include <iostream>
#include <vector>
#include <list>
using namespace std;
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

//=====================================Two pointer type==========================================

int fibo01(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = n;
    if (dp[n] != 0)
        return dp[n];
    int a = fibo01(n - 1, dp);
    int b = fibo01(n - 2, dp);
    return dp[n] = a + b;
}
int fibo02(int N, vector<int> &dp)
{
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }
        int a = dp[n - 1];
        int b = dp[n - 2];
        dp[n] = a + b;
    }
    return dp[N];
}
int fibo03(int n)
{
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++)
    {
        int t = a + b;
        a = b;
        b = t;
    }
    return b;
}
void fibo()
{
    int n = 7;
    vector<int> dp(n + 1, 0);
    // cout << fibo01(n, dp) << "\n";
    // cout << fibo02(n, dp) << "\n";
    cout << fibo03(5);
    // print(dp);
}
vector<vector<int>> dirA{{1, 0}, {0, 1}, {1, 1}};
int mazePath(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
        return dp[sr][sc] = 1;
    if (dp[sr][sc] != -1)
        return dp[sr][sc];
    int cnt = 0;
    for (int i = 0; i < dirA.size(); i++)
    {
        int x = sr + dirA[i][0];
        int y = sc + dirA[i][1];
        if (x >= 0 && y >= 0 && x <= er && y <= ec)
            cnt += mazePath(x, y, er, ec, dp);
    }
    return dp[sr][sc] = cnt;
}
int mazePathDp(int SR, int SC, int ER, int EC, vector<vector<int>> &dp)
{
    for (int sr = ER; sr >= 0; sr--)
    {
        for (int sc = EC; sc >= 0; sc--)
        {
            if (sr == ER && sc == EC)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int cnt = 0;
            for (int i = 0; i < dirA.size(); i++)
            {
                int x = sr + dirA[i][0];
                int y = sc + dirA[i][1];
                if (x >= 0 && y >= 0 && x <= ER && y <= EC)
                    cnt += dp[x][y];
            }
            dp[sr][sc] = cnt;
        }
    }
    return dp[0][0];
}
int mazePathJumps(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }
    if (dp[sr][sc] != -1)
        return dp[sr][sc];
    int cnt = 0;
    for (int i = 0; i < dirA.size(); i++)
    {
        for (int jump = 1; jump <= 2; jump++)
        {
            int x = sr + jump * dirA[i][0];
            int y = sc + jump * dirA[i][1];
            if (x <= er && y <= ec && x >= 0 && y >= 0)
                cnt += mazePathJumps(x, y, er, ec, dp);
        }
    }
    return dp[sr][sc] = cnt;
}
int mazePathJumpsDp(int ER, int EC, vector<vector<int>> &dp)
{
    for (int sr = ER; sr >= 0; sr--)
    {
        for (int sc = EC; sc >= 0; sc--)
        {
            if (sr == ER || sc == EC)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int cnt = 0;
            for (int i = 0; i < dirA.size(); i++)
            {
                for (int jump = 1; jump <= 2; jump++)
                {
                    int x = sr + jump * dirA[i][0];
                    int y = sc + jump * dirA[i][1];
                    if (x <= ER && y <= EC && x >= 0 && y >= 0)
                        cnt += dp[x][y];
                }
            }
            dp[sr][sc] = cnt;
        }
    }
    return dp[0][0];
}
int minPathSum(int sr, int sc, int er, int ec, vector<vector<int>> &dp, vector<vector<int>> &maze)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = maze[sr][sc];
    }
    if (dp[sr][sc] != -1)
        return dp[sr][sc];
    int cnt = (int)1e8;
    if (sr + 1 <= er)
        cnt = min(cnt, minPathSum(sr + 1, sc, er, ec, dp, maze));
    if (sc + 1 <= ec)
        cnt = min(cnt, minPathSum(sr, sc + 1, er, ec, dp, maze));
    return dp[sr][sc] = cnt + maze[sr][sc];
}
int minPathSumDp(int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &maze)
{
    for (int sr = ER; sr >= 0; sr--)
    {
        for (int sc = EC; sc >= 0; sc--)
        {
            if (sr == ER && sc == EC)
            {
                dp[sr][sc] = maze[sr][sc];
                continue;
            }
            int cnt = (int)1e8;
            if (sr + 1 <= ER)
                cnt = min(cnt, dp[sr + 1][sc]);
            if (sc + 1 <= EC)
                cnt = min(cnt, dp[sr][sc + 1]);
            dp[sr][sc] = cnt + maze[sr][sc];
        }
    }
    return dp[0][0];
}
int goldMineDp(int ER, int EC, vector<vector<int>> &M, vector<vector<int>> &dp)
{
    for (int sc = EC; sc >= 0; sc--)
    {
        for (int sr = ER; sr >= 0; sr--)
        {
            if (sc == EC)
            {
                dp[sr][sc] = M[sr][sc];
                continue;
            }
            int faith = -1e8;
            if (sr - 1 >= 0 && sc + 1 <= EC)
                faith = max(faith, dp[sr - 1][sc + 1]);
            if (sc + 1 <= EC)
                faith = max(faith, dp[sr][sc + 1]);
            if (sr + 1 <= ER && sc + 1 <= EC)
                faith = max(faith, dp[sr + 1][sc + 1]);
            dp[sr][sc] = faith + M[sr][sc];
        }
    }
    int rv = -100;
    for (int i = 0; i <= ER; i++)
    {
        rv = max(rv, dp[i][0]);
    }
    return rv;
}
int climbStairs(int n, int tar, vector<int> &dp)
{
    if (n == tar)
    {
        return dp[n] = 1;
    }
    if (dp[n] != -1)
        return dp[n];
    int one = 0, two = 0;
    if (n + 1 <= tar)
        one = climbStairs(n + 1, tar, dp);
    if (n + 2 <= tar)
        two = climbStairs(n + 2, tar, dp);
    return dp[n] = one + two;
}
int climbStairsDp(int tar, vector<int> &dp)
{
    for (int n = tar; n >= 0; n--)
    {
        if (n == tar)
        {
            dp[n] = 1;
            continue;
        }
        int one = 0, two = 0;
        if (n + 1 <= tar)
            one = dp[n + 1];
        if (n + 2 <= tar)
            two = dp[n + 2];
        dp[n] = one + two;
    }
    return dp[0];
}
int minCostStair(int tar, vector<int> &cost, vector<int> &dp)
{
    if (tar < 1)
    {
        return dp[tar] = cost[tar];
    }
    if (dp[tar] != -1)
        return dp[tar];
    int one = 1e8, two = 1e8;
    one = minCostStair(tar - 1, cost, dp);
    if (tar - 2 >= 0)
        two = minCostStair(tar - 2, cost, dp);
    return dp[tar] = min(one, two) + cost[tar];
}
int minCostStairDp(vector<int> &cost, vector<int> &dp)
{
    for (int tar = 0; tar < dp.size(); tar++)
    {
        if (tar < 1)
        {
            dp[tar] = cost[tar];
            continue;
        }
        if (dp[tar] != -1)
            return dp[tar];
        int one = 1e8, two = 1e8;
        one = dp[tar - 1];
        if (tar - 2 >= 0)
            two = dp[tar - 2];
        dp[tar] = min(one, two) + cost[tar];
    }
    return dp[dp.size() - 1];
}
int dicePath(int n, vector<int> &dp)
{
    if (n == 0)
    {
        return dp[n] = 1;
    }
    if (dp[n] != -1)
        return dp[n];
    int cnt = 0;
    for (int i = 1; i <= 6; i++)
    {
        if (n - i >= 0)
            cnt += dicePath(n - i, dp);
    }
    return dp[n] = cnt;
}
int dicePathDp(int N, vector<int> &dp)
{
    for (int n = 0; n <= N; n++)
    {
        if (n == 0)
        {
            dp[n] = 1;
            continue;
        }
        int cnt = 0;
        for (int i = 1; i <= 6; i++)
        {
            if (n - i >= 0)
                cnt += dp[n-i];
        }
        dp[n] = cnt;
    }
    return dp[N];
}
void mazePath()
{
    vector<vector<int>> dp(3, vector<int>(3, -1));
    // cout << mazePathDp(0, 0, 2, 2, dp) << "\n";
    // cout << mazePathJumpsDp(2, 2, dp) << "\n";
    vector<vector<int>> maze{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSumDp(2, 2, dp, maze) << "\n";
    print2d(dp);
}
void climbstairs()
{
    int tar = 10;
    vector<int> cost{3, 1, 5, 6, 8, 7};
    vector<int> dp(tar + 1, -1);
    // cout << climbStairsDp(tar, dp) << "\n";
    // cout << minCostStairDp(cost, dp) << "\n";
    cout << dicePathDp(tar, dp) << "\n";
    print(dp);
}
void twoPointer()
{
    // mazePath();
    // fibo();
    climbstairs();
}

void solve()
{
    // g++ l01.cpp -o p && ./p > output.txt
    twoPointer();
}
int main()
{
    solve();
    return 0;
}