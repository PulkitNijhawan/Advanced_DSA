#include <iostream>
#include <vector>
#include <list>
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
    for (vector<int> arr : dp)
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
                cnt += dp[n - i];
        }
        dp[n] = cnt;
    }
    return dp[N];
}
int dicePathbtr(int N)
{ //T:O(n) precise
    //S:O(6)
    list<int> ll;
    ll.push_back(1);
    int psum = 1;
    for (int n = 1; n <= N; n++)
    {
        if (ll.size() < 6)
        {
            ll.push_back(psum);
            psum += ll.back();
        }
        else
        {
            ll.push_back(psum);
            psum += ll.back();
            psum -= ll.front();
            ll.pop_front();
        }
    }
    return ll.back();
}
void climbstairs()
{
    int tar = 10;
    vector<int> cost{3, 1, 5, 6, 8, 7};
    vector<int> dp(tar + 1, -1);
    // cout << climbStairsDp(tar, dp) << "\n";
    // cout << minCostStairDp(cost, dp) << "\n";
    // cout << dicePathDp(tar, dp) << "\n";
    cout << dicePathbtr(10) << "\n";
    print(dp);
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
long solve(string &s, int idx, vector<long> &dp)
{
    if (s[idx] == '0')
        return dp[idx] = 0;
    if (s.length() == idx)
        return dp[idx] = 1;
    if (dp[idx] != -1)
        return dp[idx];
    int cnt = 0;
    if (s[idx] == '*')
    {
        for (int i = 1; i <= 9; i++)
            cnt = ((cnt % mod) + (solve(s, idx + 1, dp) % mod)) % mod; //one call
        if (s.length() - idx >= 2)
        {
            if (s[idx + 1] != '*')
            {
                int ch2 = s[idx + 1] - '0';
                if (ch2 <= 6)
                    cnt += (2 * (solve(s, idx + 2, dp) % mod)) % mod; //2calls
                else
                    cnt = ((cnt % mod) + (solve(s, idx + 2, dp) % mod)) % mod; //2 calls
            }
            else
            {
                for (int i = 1; i <= 15; i++)
                    cnt = ((cnt % mod) + (solve(s, idx + 2, dp) % mod)) % mod; //2calls
            }
        }
    }
    else
    {
        int one = s[idx] - '0';

        if (one != 0)
            cnt = ((cnt % mod) + (solve(s, idx + 1, dp) % mod)) % mod; //one call
        if (s.length() - idx >= 2)
        {
            if (s[idx + 1] != '*')
            {
                int two = (s[idx] - '0') * 10 + (s[idx + 1] - '0');
                if (two > 9 && two <= 26)
                    cnt = ((cnt % mod) + (solve(s, idx + 2, dp) % mod)) % mod; //two calls
            }
            else
            {
                if (one == 1)
                    for (int i = 1; i <= 9; i++)
                        cnt = ((cnt % mod) + (solve(s, idx + 2, dp) % mod)) % mod; //two calls
                else if (one == 2)
                    for (int i = 1; i <= 6; i++)
                        cnt = ((cnt % mod) + (solve(s, idx + 2, dp) % mod)) % mod; //two calls
            }
        }
    }
    return dp[idx] = cnt;
}
void numDecodings(string s)
{
    vector<long> dp(s.length() + 1, -1);
    cout << solve(s, 0, dp) << "\n";
    for (long x : dp)
        cout << x << " ";
}
void twoPointer()
{
    numDecodings("1*0*7*");
    // mazePath();
    // fibo();
    // climbstairs();
}
//===========================================================String Set==========================================================

void palindromicSubstring(string str, vvi &dp)
{
    int n = str.length();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1)
                dp[i][j] = str[i] == str[j];
            else
                dp[i][j] = str[i] == str[j] && dp[i + 1][j - 1];
        }
    }
}
int longPalindromicSubstring(string str, vvi &dp)
{
    int n = str.length();
    int ans = -1;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1)
                dp[i][j] = str[i] == str[j] ? 2 : 0;
            else
                dp[i][j] = str[i] == str[j] ? dp[i + 1][j - 1] + 2 : 0;
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}
vi countPalindromicSubstring(string str, vvi &dp)
{
    vi ans(2);
    int l = 0, h = 0;
    int n = dp.size();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            ans[0] += dp[i][j];
            if (dp[i][j])
            {
                ans[1] = j - i + 1;
                h = j;
                l = i;
            }
        }
    }
    cout << str.substr(l, h - l + 1) << "\n";
    return ans;
}
int longPalindromicSubseq(string str, int i, int j, vvi &dp)
{
    if (i > j)
        return dp[i][j] = 0;
    if (i == j)
        return dp[i][j] = 1;
    if (dp[i][j] != 0)
        return dp[i][j];
    int tendency = -1;
    if (str[i] == str[j])
        tendency = longPalindromicSubseq(str, i + 1, j - 1, dp) + 2;
    else
    {
        tendency = max(tendency, longPalindromicSubseq(str, i + 1, j, dp));
        tendency = max(tendency, longPalindromicSubseq(str, i, j - 1, dp));
    }
    return dp[i][j] = tendency;
}
int longPalindromicSubseqDp(string str, vvi &dp)
{
    int n = str.length();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }
            int tendency = -1;
            if (str[i] == str[j])
                tendency = dp[i + 1][j - 1] + 2;
            else
            {
                tendency = max(tendency, dp[i + 1][j]);
                tendency = max(tendency, dp[i][j - 1]);
            }
            dp[i][j] = tendency;
        }
    }
    return dp[0][n - 1];
}
// int longPalindromicSubseq_btr(string str, int i, int j, vvi &dp, vvi &dpstr)
// {
//     if (i > j)
//         return dp[i][j] = 0;
//     if (i == j)
//         return dp[i][j] = 1;
//     if (dpstr[i][j] != 0)
//         return dp[i][j] = dpstr[i][j];                             //FIND RIGHT SOLUTION
//     if (dp[i][j] != 0)
//         return dp[i][j];
//     int tendency = -1;
//     if (str[i] == str[j])
//         tendency = longPalindromicSubseq_btr(str, i + 1, j - 1, dp, dpstr);
//     else
//     {
//         tendency = max(tendency, longPalindromicSubseq_btr(str, i + 1, j, dp, dpstr));
//         tendency = max(tendency, longPalindromicSubseq_btr(str, i, j - 1, dp, dpstr));
//     }
//     return tendency;
// }
int distinctSubseq(string &s, string &t, int n, int m, vvi &dp)
{
    if (m > n)
        return dp[n][m] = 0;
    if (m == 0)
        return dp[n][m] = 1;
    if (dp[n][m] != -1)
        return dp[n][m];
    int tendency = 0;
    if (s[n] == t[m])
    {
        tendency += distinctSubseq(s, t, n - 1, m - 1, dp);
        tendency += distinctSubseq(s, t, n - 1, m, dp);
    }
    else
    {
        tendency += distinctSubseq(s, t, n - 1, m, dp);
    }
    return dp[n][m] = tendency;
}
int countPalindromicSubseq(string &str, int i, int j, vvi &dp)
{
    if (i > j)
        return dp[i][j] = 0;
    if (i == j)
        return dp[i][j] = 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    int x = countPalindromicSubseq(str, i + 1, j - 1, dp);
    int y = countPalindromicSubseq(str, i, j - 1, dp);
    int z = countPalindromicSubseq(str, i + 1, j, dp);
    int tendency = 0;
    if (str[i] == str[j])
        tendency += y + z + 1;
    else
        tendency += y + z - x;
    return dp[i][j] = tendency;
}
int longestCommonSubseq(string &s, string &t, int n, int m, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
        return 0;
    if (dp[n][m] != -1)
        return dp[n][m];
    int tendency = -1;
    if (s[n - 1] == t[m - 1])
        tendency = longestCommonSubseq(s, t, n - 1, m - 1, dp) + 1;
    else
    {
        tendency = max(tendency, longestCommonSubseq(s, t, n - 1, m, dp));
        tendency = max(tendency, longestCommonSubseq(s, t, n, m - 1, dp));
    }
    return dp[n][m] = tendency;
}
int longestCommonSubseqDp(string &s, string &t, int N, int M, vector<vector<int>> &dp)
{
    for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            if (n == 0 || m == 0)
            {
                dp[n][m] = 0;
                continue;
            }
            int tendency = -1;
            if (s[n - 1] == t[m - 1])
                tendency = dp[n - 1][m - 1] + 1;
            else
            {
                tendency = max(tendency, dp[n - 1][m]);
                tendency = max(tendency, dp[n][m - 1]);
            }
            dp[n][m] = tendency;
        }
    }
    return dp[N][M];
}
int editDistance(string &s, string &t, int n, int m, vvi &dp)
{
    if (n == 0 || m == 0)
        return dp[n][m] = max(n, m);
    if (dp[n][m] != -1)
        return dp[n][m];
    int tendency = 1e8;
    if (s[n - 1] == t[m - 1])
        tendency = editDistance(s, t, n - 1, m - 1, dp);
    else
    {
        tendency = min(tendency, editDistance(s, t, n, m - 1, dp));
        tendency = min(tendency, editDistance(s, t, n - 1, m, dp));
        tendency = min(tendency, editDistance(s, t, n - 1, m - 1, dp));
        tendency++;
    }
    return dp[n][m] = tendency;
}
void palindromics()
{
    // string str = "abcbddbcaab";
    // int n = str.length();
    // vvi dpstr(n, vi(n, 0));
    // longPalindromicSubstring(str, dpstr);
    // vi ans = countPalindromicSubstring(str, dpstr);
    // print(ans);
    // print2d(dpstr);
    // vvi dp(n, vi(n, 0));
    // cout << longPalindromicSubseqDp(str, dp) << "\n";
    // cout << longPalindromicSubseq_btr(str, 0, n - 1, dp, dpstr) << "\n";
    // print2d(dp);
    string s = "rabbbit", t = "rabbit";
    int n = s.length(), m = t.length();
    vvi dp(n + 1, vi(m + 1, -1));
    cout << distinctSubseq(s, t, n, m, dp) << "\n";
    print2d(dp);
}

void stringSet()
{
    palindromics();
}
//===========================================================Target Set====================================================================
int coinChangePermute(int target, vi &arr, vi &dp)
{
    if (target == 0)
    {
        return dp[target] = 1;
    }
    if (dp[target] != -1)
        return dp[target];
    int tendency = 0;
    for (int ele : arr)
    {
        if (target - ele >= 0)
            tendency += coinChangePermute(target - ele, arr, dp);
    }
    return dp[target] = tendency;
}
int coinChangePermuteDp(int T, vi &arr, vi &dp)
{
    for (int target = 0; target <= T; target++)
    {
        if (target == 0)
        {
            dp[target] = 1;
            continue;
        }
        int tendency = 0;
        for (int ele : arr)
        {
            if (target - ele >= 0)
                tendency += dp[target - ele];
        }
        dp[target] = tendency;
    }
    return dp[T];
}
int coinChangeCombiDp(int T, vi &arr, vi &dp)
{
    dp[0] = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        int ele = arr[i];
        for (int target = ele; target <= T; target++)
        {
            dp[target] += dp[target - ele];
        }
    }
    return dp[T];
}

//Leetcode 322 TRY
int coinChangeLC(int tar, vi &arr, vi &dp)
{
    if (tar == 0)
    {
        return dp[tar] = 0;
    }
    if (dp[tar] != -1)
        return dp[tar];
    int tendency = 1e9;
    for (int ele : arr)
    {
        if (tar - ele >= 0)
        {
            int val = coinChangeLC(tar - ele, arr, dp);
            if (val != 1e9 && val + 1 < tendency)
                tendency = val + 1;
        }
    }
    return dp[tar] = tendency == -1 ? -1 : tendency + 1;
}
int coinChangeCombiLim(int tar, vi &arr, vvi &dp, int n)
{
    if (tar == 0 || n == 0)
    {
        return dp[n][tar] = tar == 0 ? 1 : 0;
    }
    if (dp[n][tar] != -1)
        return dp[n][tar];
    int tendency = 0;
    if (tar - arr[n - 1] >= 0)
        tendency += coinChangeCombiLim(tar - arr[n - 1], arr, dp, n - 1);
    tendency += coinChangeCombiLim(tar, arr, dp, n - 1);
    return dp[n][tar] = tendency;
}
int knapsack01(int tar, vi &w, vi &c, vvi &dp, int idx)
{
    if (idx == w.size() || tar == 0)
    {
        return dp[idx][tar] = 0;
    }
    if (dp[idx][tar] != -1)
        return dp[idx][tar];
    int tendency = 0;
    if (tar - w[idx + 1] >= 0)
        tendency = knapsack01(tar - w[idx + 1], w, c, dp, idx + 1) + c[idx];
    tendency = max(tendency, knapsack01(tar, w, c, dp, idx + 1));
    return dp[idx][tar] = tendency;
}
int coinChangeCombiLimPath(vi &arr, int tar, int n, vvi &dp, string path)
{
    if (tar == 0 || n == 0)
    {
        if (tar == 0)
        {
            cout << path << "\n";
            return 1;
        }
        return 0;
    }
    int tendency = 0;
    if (tar - arr[n - 1] >= 0 && dp[n - 1][tar - arr[n - 1]] > 0)
        tendency += coinChangeCombiLimPath(arr, tar - arr[n - 1], n - 1, dp, path + to_string(arr[n - 1]) + " ");
    if (dp[n - 1][tar] > 0)
        tendency += coinChangeCombiLimPath(arr, tar, n - 1, dp, path + " ");
    return tendency;
}
void equiset()
{
    vi arr{1, 5, 11, 5};
    int sum = 0;
    for (int ele : arr)
        sum += ele;
    int tar = sum / 2;
    if (tar % 2 != 0)
    {
        cout << false << "\n";
        return;
    }
    vvi dp(arr.size() + 1, vi(tar + 1, -1));
    coinChangeCombiLim(tar, arr, dp, 0);
}
int unboundedKnapsack(int tar, vi &w, vi &c, vi &dp)
{
    dp[0] = 0;
    int costIdx = 0;
    for (int ele : w)
    {
        for (int i = ele; i <= tar; i++)
        {
            dp[i] = max(dp[i], dp[i - ele] + c[costIdx]);
        }
        costIdx++;
    }
    return dp[tar];
}
int solution4Equations(vi &coeff, int tar, vi &dp)
{
    dp[0] = 1;
    for (int ele : coeff)
    {
        for (int i = ele; i <= tar; i++)
        {
            dp[i] += dp[i - ele];
        }
    }
    return dp[tar];
}
int targetSumLC(vi &arr, int tar, int n, int sum, vvi &dp)
{
    if (n == 0)
    {
        return dp[n][sum] = tar == sum ? 1 : 0;
    }
    if (dp[n][sum] != -1)
        return dp[n][sum];
    int tendency = 0;
    tendency += targetSumLC(arr, tar, n - 1, sum + arr[n - 1], dp);
    tendency += targetSumLC(arr, tar, n - 1, sum - arr[n - 1], dp);
    return dp[n][sum] = tendency;
}
void targetSet()
{
    int tar = 3;
    // vi arr{2, 3, 5, 7};
    // vi dp(target + 1, -1);
    // cout << coinChangePermute(target, arr, dp) << "\n";
    // print(dp);
    // int tar = 5;
    // vi w{1,2,3};
    // vi c{60, 100, 120};
    // vvi dp(tar + 1, vi(w.size() + 1, -1));
    // cout << coinChangeCombiLim(tar, arr, dp, arr.size()) << "\n";
    // cout << knapsack01(tar, w, c, dp, 0) << "\n";
    // print2d(dp);
    // vi w{1, 3, 4, 5};
    // vi c{10, 40, 50, 70};
    // vi dp(tar + 1, -1);
    // cout << unboundedKnapsack(tar, w, c, dp) << "\n";
    // vi coeff{1, 2};
    // vi dp(tar + 1, 0);
    // cout << solution4Equations(coeff, tar, dp) << "\n";
    // print(dp);
    vi arr{1, 1, 1, 1, 1};
    int sum = 0;
    for (int ele : arr)
        sum += ele;
    vvi dp(arr.size() + 1, vi(2 * sum + 1, -1));
    if (sum < tar || sum < -tar)
        cout << -1;
    cout << targetSumLC(arr, tar + sum, arr.size(), sum, dp) << "\n";
    print2d(dp);
}
void solve()
{
    // g++ l01.cpp -o p && ./p > output.txt
    // twoPointer();
    // stringSet();
    targetSet();
}
int main()
{
    solve();
    return 0;
}