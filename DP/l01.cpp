
#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <cstring>
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
//=======================Fibo============================================================
vector<vector<int>> I = {{1, 0}, {1, 1}};
int fiboRec(int n)
{
    if (n <= 1)
        return n;
    return fiboRec(n - 1) + fiboRec(n - 2);
}
int fiboMemo(int n, vector<int> &dp)
{
    if (n <= 1)
    {
        return dp[n] = n;
    }
    if (dp[n] != 0)
        return dp[n];
    return dp[n] = fiboMemo(n - 1, dp) + fiboMemo(n - 2, dp);
}
int fiboDP(int n, vector<int> &dp)
{
    for (int n = 0; n < dp.size(); n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }
        dp[n] = dp[n - 1] + dp[n - 2];
    }
    return dp[dp.size() - 1];
}
int fibo_btr(int n)
{
    int a = 0;
    int b = 1;
    for (int i = 2; i <= n; i++)
    {
        int sum = a + b;
        a = b;
        b = sum;
    }
    return a;
}
vector<vector<int>> multiply(vector<vector<int>> &one, vector<vector<int>> &two)
{
    vector<vector<int>> ans(2, vector<int>(2));
    ans[0][0] = one[0][0] * two[0][0] + one[0][1] * two[1][0];
    ans[0][1] = one[0][0] * two[0][1] + one[0][1] * two[1][1];
    ans[1][0] = one[1][0] * two[0][0] + one[1][1] * two[1][0];
    ans[1][1] = one[1][0] * two[0][1] + one[1][1] * two[1][1];
    return ans;
}
vector<vector<int>> fiboLogn(int n)
{
    if (n == 1)
        return I;
    vector<vector<int>> recAns = fiboLogn(n / 2);
    recAns = multiply(recAns, recAns);
    return n % 2 != 0 ? multiply(recAns, I) : recAns;
}

void fiboSet()
{
    // vector<int> dp(6, 0);
    // cout << fiboDP(5, dp) << endl;
    // display(dp);
    cout << fiboLogn(5)[0][1];
}
//===================================MazeSet============================================
int mazeRec(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return 1;
    int cnt = 0;
    if (sr + 1 <= er)
    {
        cnt += mazeRec(sr + 1, sc, er, ec);
    }
    if (sc + 1 <= ec)
    {
        cnt += mazeRec(sr, sc + 1, er, ec);
    }
    return cnt;
}
int mazeMemo(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
        return dp[sr][sc] = 1;
    if (dp[sr][sc] != 0)
        return dp[sr][sc];
    int cnt = 0;
    if (sr + 1 <= er)
    {
        cnt += mazeMemo(sr + 1, sc, er, ec, dp);
    }
    if (sc + 1 <= ec)
    {
        cnt += mazeMemo(sr, sc + 1, er, ec, dp);
    }
    return dp[sr][sc] = cnt;
}
int mazeDP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int cnt = 0;
            if (sr + 1 <= er)
            {
                cnt += dp[sr + 1][sc];
            }
            if (sc + 1 <= ec)
            {
                cnt += dp[sr][sc + 1];
            }
            dp[sr][sc] = cnt;
        }
    }
    return dp[0][0];
}
int mazePathMulti(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    for (int jump = 1; sr + jump <= er; jump++)
        count += mazePathMulti(sr + jump, sc, er, ec, dp);

    for (int jump = 1; sc + jump <= ec; jump++)
        count += mazePathMulti(sr, sc + jump, er, ec, dp);

    for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
        count += mazePathMulti(sr + jump, sc + jump, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazePathMulti_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{

    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            for (int jump = 1; sr + jump <= er; jump++)
                count += dp[sr + jump][sc]; //mazePathMulti(sr + jump, sc, er, ec, dp);

            for (int jump = 1; sc + jump <= ec; jump++)
                count += dp[sr][sc + jump]; //mazePathMulti(sr, sc + jump, er, ec, dp);

            for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
                count += dp[sr + jump][sc + jump]; //mazePathMulti(sr + jump, sc + jump, er, ec, dp);

            dp[sr][sc] = count;
        }
    }

    return dp[0][0];
}

void mazeSet()
{
    vector<vector<int>> dp(3, vector<int>(3, 0));
    // cout << mazeDP(0, 0, 2, 2, dp) << endl;
    cout << mazePathMulti_DP(0, 0, 2, 2, dp) << endl;
    display2D(dp);
}
//=================================coinChange===========================================
int diceMemo(int tar, vector<int> &dp)
{
    if (tar == 0)
        return 1;
    if (dp[tar] != 0)
        return dp[tar];
    int cnt = 0;
    for (int i = 1; i <= 6; i++)
    {
        if ((tar - i) >= 0)
            cnt += diceMemo(tar - i, dp);
    }
    return dp[tar] = cnt;
}
int diceDP(int tar, vector<int> &dp)
{

    for (tar = 0; tar < dp.size(); tar++)
    {
        if (tar == 0)
        {
            dp[tar] = 1;
            continue;
        }
        int cnt = 0;
        for (int i = 1; i <= 6; i++)
        {
            if ((tar - i) >= 0)
                cnt += dp[tar - i];
        }
        dp[tar] = cnt;
    }
    return dp[dp.size() - 1];
}
int dice_btr(int tar)
{
    list<int> ll;
    for (int i = tar; i >= 0; i--)
    {
        if (i > tar - 2)
        {
            ll.push_front(1);
            continue;
        }
        if (ll.size() <= 6)
        {
            ll.push_front(2 * ll.front());
        }
        else
        {
            ll.push_front(2 * ll.front() - ll.back());
            ll.pop_back();
        }
    }
    return ll.front();
}
int coinMemo(int tar, vector<int> &dp, vector<int> &choices)
{
    if (tar == 0)
        return dp[tar] = 1;
    if (dp[tar] != 0)
        return dp[tar];
    int cnt = 0;
    for (int i = 0; i < choices.size(); i++)
    {
        cnt += coinMemo(tar - choices[i], dp, choices);
    }
    return dp[tar] = cnt;
}
int coinDP(int tar, vector<int> &dp, vector<int> &choices)
{
    for (tar = 0; tar < dp.size(); tar++)
    {
        if (tar == 0)
        {
            dp[tar] = 1;
            continue;
        }
        int cnt = 0;
        for (int i = 0; i < choices.size(); i++)
        {
            cnt += coinMemo(tar - choices[i], dp, choices);
        }
        return dp[tar] = cnt;
    }
    return dp[dp.size() - 1];
}
// int targetSum(vector<int> &coins, int tar, int idx, vector<vector<int>> &dp)
// {
//     if (tar == 0 || idx == coins.size())
//     {
//         if (tar == 0)
//             return dp[idx][tar] = 1;
//         return dp[idx][tar] = 0;
//     }
//     if (dp[idx][tar] != 0)
//         return dp[idx][tar];
//     int cnt = 0;
//     if (tar - coins[idx] >= 0)
//         cnt += targetSum(coins, tar - coins[idx], idx + 1, dp);
//     cnt += targetSum(coins, tar, idx + 1, dp);
//     return dp[idx][tar] = cnt;
// }
// leecode: https://leetcode.com/problems/min-cost-climbing-stairs/
// leecode 322
void coinChange()
{
    vector<int> coins = {20, 30, 50, 70};
    int tar = 100;
    vector<vector<int>> dp(coins.size() + 1, vector<int>(tar + 1, 0));
    // cout << targetSum(coins, 100, 0, dp) << endl;
    display2D(dp);
    // vector<int> dp(11, 0);
    // cout << diceDP(10, dp) << endl;
    // display(dp);
}
//==================================MinPaths============================================
int minPathMemo(int sr, int sc, vector<vector<int>> &arr, vector<vector<int>> &dp)
{
    if (sr == arr.size() - 1 && sc == arr[0].size() - 1)
    {
        return dp[sr][sc] = arr[sr][sc];
    }
    if (dp[sr][sc] != -1)
        return dp[sr][sc];
    int myAns = INT_MAX;
    if (sr + 1 < arr.size())
        myAns = min(myAns, minPathMemo(sr + 1, sc, arr, dp));
    if (sc + 1 < arr[0].size())
        myAns = min(myAns, minPathMemo(sr, sc + 1, arr, dp));
    return dp[sr][sc] = myAns + arr[sr][sc];
}
int minPathDP(vector<vector<int>> &arr, vector<vector<int>> &dp)
{
    for (int sr = arr.size() - 1; sr >= 0; sr--)
    {
        for (int sc = arr[0].size() - 1; sc >= 0; sc--)
        {
            if (sr == arr.size() - 1 && sc == arr[0].size() - 1)
            {
                dp[sr][sc] = arr[sr][sc];
                continue;
            }
            int myAns = INT_MAX;
            if (sr + 1 < arr.size())
                myAns = min(myAns, dp[sr + 1][sc]);
            if (sc + 1 < arr[0].size())
                myAns = min(myAns, dp[sr][sc + 1]);
            dp[sr][sc] = myAns + arr[sr][sc];
        }
    }
    return dp[0][0];
}
vector<vector<int>> dirA = {{-1, 1}, {0, 1}, {1, 1}};
int goldMemo(int sr, int sc, vector<vector<int>> &arr, vector<vector<int>> &dp)
{
    if (sr == arr.size() - 1 && sc == arr[0].size() - 1)
    {
        return dp[sr][sc] = arr[sr][sc];
    }
    if (dp[sr][sc] != -1)
        return dp[sr][sc];
    int myAns = 0;
    for (int i = 0; i < dirA.size(); i++)
    {
        int x = sr + dirA[i][0];
        int y = sc + dirA[i][1];
        if (x >= 0 && y >= 0 && x < arr.size() && y < arr[0].size())
        {
            myAns = max(myAns, goldMemo(x, y, arr, dp));
        }
    }
    return dp[sr][sc] = myAns + arr[sr][sc];
}
void minPathSet()
{
    vector<vector<int>> arr = {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}};
    vector<vector<int>> dp(arr.size(), vector<int>(arr[0].size(), -1));
    // cout << minPathDP(arr, dp) << endl;
    int goldAns = -2;
    for (int i = 0; i < dp.size(); i++)
    {
        goldAns = max(goldAns, goldMemo(i, 0, arr, dp));
    }

    display2D(dp);
}
//=================================pairprob============================================================
int friendPairMemo(int n, vector<int> &dp)
{
    if (n <= 2)
    {
        return dp[n] = n;
    }
    if (dp[n] != -1)
        return dp[n];
    int alone = friendPairMemo(n - 1, dp);
    int pairUp = (n - 1) * (friendPairMemo(n - 2, dp));
    return dp[n] = alone + pairUp;
}
int friendPairDP(int n, vector<int> &dp)
{
    for (n = 1; n < dp.size(); n++)
    {
        if (n <= 2)
        {
            dp[n] = n;
            continue;
        }
        int alone = dp[n - 1];
        int pairUp = (n - 1) * dp[n - 2];
        dp[n] = alone + pairUp;
    }
    return dp[dp.size() - 1];
}
int nInKMemo(int n, int k, vector<vector<int>> &dp)
{
    if (n == k)
    {
        return dp[k][n] = 1;
    }
    if (k == 1)
        return dp[k][n] = 1;
    if (dp[k][n] != -1)
        return dp[k][n];
    int existingGrp = nInKMemo(n - 1, k, dp) * k;
    int newGrp = nInKMemo(n - 1, k - 1, dp);
    return dp[k][n] = newGrp + existingGrp;
}
int count_of_ways_DP(int n, int k, vector<vector<int>> &dp)
{

    int K = k, N = n;
    for (k = 0; k <= K; k++)
    {
        for (n = 0; n <= N; n++)
        {
            if (k == 0)
            {
                continue;
            }
            if (n < k)
                continue;
            if (n == k)
            {
                dp[k][n] = 1;
                continue;
            }
            if (k == 1)
            {
                dp[k][n] = 1;
                continue;
            }

            int newGroup = dp[k - 1][n - 1];
            int ExistingGroup = dp[k][n - 1] * k;

            dp[k][n] = newGroup + ExistingGroup;
        }
    }

    return dp[K][N];
}
void pairingProbSet()
{
    int n = 4, k = 2;
    // vector<int> dp(n + 1, -1);
    // cout << friendPairDP(n, dp) << endl;
    // display(dp);
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1));
    cout << count_of_ways_DP(n, k, dp) << endl;

    display2D(dp);
}
//=================================Strings=============================================================
vector<vector<bool>> palindrome(string str)
{
    vector<vector<bool>> dp(str.length(), vector<bool>(str.length(), false));
    for (int gap = 0; gap < str.length(); gap++)
    {
        for (int i = 0, j = gap; j < str.length(); i++, j++)
        {
            if (i == j)
                dp[i][j] = true;
            else if (str[i] == str[j] && gap == 1)
                dp[i][j] = true;
            else if (str[i] == str[j] && dp[i + 1][j - 1])
                dp[i][j] = true;
        }
    }
    return dp;
}
string longestPalinSubstringDP(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int maxLen = 0;
    int si = 0;
    int ei = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 2;
            else if (str[i] == str[j] && dp[i + 1][j - 1] > 0)
                dp[i][j] = dp[i + 1][j - 1] + 2;

            if (dp[i][j] > maxLen)
            {
                maxLen = dp[i][j];
                ei = j;
                si = i;
            }
        }
    }
    return str.substr(si, ei - si + 1);
}
int countPalindromeSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int cnt = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 1;
            else if (str[i] == str[j] && dp[i + 1][j - 1] > 0)
                dp[i][j] = 1;

            cnt += dp[i][j];
        }
    }
    return cnt;
}
int longestPalindromicSubseqMemo(string &str, int i, int j, vector<vector<int>> &dp)
{
    if (i > j)
        return dp[i][j] = 0;
    if (j == i)
        return dp[i][j] = 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    int len = 0;
    if (str[i] == str[j])
    {
        len = longestPalindromicSubseqMemo(str, i + 1, j - 1, dp) + 2;
    }
    else
    {
        len = max(longestPalindromicSubseqMemo(str, i, j - 1, dp), longestPalindromicSubseqMemo(str, i + 1, j, dp));
    }
    return dp[i][j] = len;
}
int longestPalindromicSubseqDP(string &str, vector<vector<int>> &dp)
{
    for (int gap = 0; gap < str.length(); gap++)
    {
        for (int i = 0, j = gap; j < str.length(); j++, i++)
        {
            if (i > j)
            {
                dp[i][j] = 0;
                continue;
            }
            if (j == i)
            {
                dp[i][j] = 1;
                continue;
            }
            int len = 0;
            if (str[i] == str[j] && gap == 1)
            {
                len = 2;
            }
            else if (str[i] == str[j])
            {
                len = dp[i + 1][j - 1] + 2;
            }

            else
            {
                len = max(dp[i][j - 1], dp[i + 1][j]);
            }
            dp[i][j] = len;
        }
    }
    return dp[0][str.length() - 1];
}
int lcsMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp)
{
    if (i == s1.length() || j == s2.length())
        return dp[i][j] = 0;
    if (dp[i][j] != -1)
        return dp[i][j];

    if (s1[i] == s2[j])
    {
        return dp[i][j] = lcsMemo(s1, s2, i + 1, j + 1, dp) + 1;
    }
    else
    {
        return dp[i][j] = max(lcsMemo(s1, s2, i + 1, j, dp), lcsMemo(s1, s2, i, j + 1, dp));
    }
    return 0;
}
int lcsDP(string &s1, string &s2, vector<vector<int>> &dp)
{
    for (int i = s1.length(); i >= 0; i--)
    {
        for (int j = s2.length(); j >= 0; j--)
        {
            if (i == s1.length() || j == s2.length())
            {
                dp[i][j] = 0;
                continue;
            }
            if (s1[i] == s2[j])
            {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
    return dp[0][0];
}
int max_ = 0;
int longestCommSubstringMemo(string &w1, string &w2, int i, int j, vector<vector<int>> &dp)
{
    if (i == w1.length() || j == w2.length())
    {
        return dp[i][j] = 0;
    }
    if (dp[i][j] != -1)
        return dp[i][j];
    int a = longestCommSubstringMemo(w1, w2, i + 1, j, dp);
    int b = longestCommSubstringMemo(w1, w2, i, j + 1, dp);
    if (w1[j] == w2[j])
    {
        int q = longestCommSubstringMemo(w1, w2, i + 1, j + 1, dp) + 1;
        max_ = max(max_, q);
        return dp[i][j] = q;
    }
    return (a == 0 || b == 0) ? max(a, b) : 0;
}
int countPS(string &str, int i, int j, vector<vector<int>> &dp)
{
    if (i > j)
        return dp[i][j] = 0;
    if (i == j)
        return dp[i][j] = 1;
    if (dp[i][j] != 0)
        return dp[i][j];

    int x = countPS(str, i + 1, j - 1, dp);
    int y = countPS(str, i + 1, j, dp);
    int z = countPS(str, i, j - 1, dp);
    return dp[i][j] = (str[i] == str[j]) ? (y + z + 1) : y + z - x;
}
int countPSDP(string &str, vector<vector<int>> &dp)
{
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[0].size(); j++)
        {
            if (i > j)
            {
                dp[i][j] = 0;
                continue;
            }
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }
            int x = dp[i + 1][j - 1];
            int y = dp[i + 1][j];
            int z = dp[i][j - 1];
            dp[i][j] = (str[i] == str[j]) ? (y + z + 1) : y + z - x;
        }
    }
    return dp[0][str.length() - 1];
}
// https://leetcode.com/problems/uncrossed-lines/
void stringSet()
{
    // string str = "abccbd";
    string w1 = "adbccf";
    string w2 = "bc";
    // // vector<vector<bool>> isPalindrome = palindrome(str);
    vector<vector<int>> dp(w1.length() + 1, vector<int>(w2.length() + 1, -1));
    // cout << longestPalindromicSubseqDP(str, dp) << endl;
    // display2D(dp);
    longestCommSubstringMemo(w1, w2, 0, 0, dp);
    cout << max_ << endl;
    // cout << lcsDP(s1, s2, dp) << endl;
    display2D(dp);
}
//===================================targetSum==========================================================
int permuInfiMemo(vector<int> &wt, int tar, vector<int> &dp)
{
    if (tar == 0)
    {
        return dp[tar] = 1;
    }
    if (dp[tar] != -1)
        return dp[tar];
    int cnt = 0;
    for (int ele : wt)
    {
        if (tar - ele >= 0)
            cnt += permuInfiMemo(wt, tar - ele, dp);
    }
    return dp[tar] = cnt;
}
int permuInfiDP(vector<int> &wt, vector<int> &dp)
{
    for (int tar = 0; tar < dp.size(); tar++)
    {
        if (tar == 0)
        {
            dp[tar] = 1;
            continue;
        }
        int cnt = 0;
        for (int ele : wt)
        {
            if (tar - ele >= 0)
                cnt += dp[tar - ele];
        }
        dp[tar] = cnt;
    }
    return dp[dp.size() - 1];
}
int combiInfiDP(vector<int> &wt, vector<int> &dp)
{
    dp[0] = 1;
    for (int ele : wt)
    {
        for (int tar = ele; tar < dp.size(); tar++)
        {
            dp[tar] += dp[tar - ele];
        }
    }
    return dp[dp.size() - 1];
}
int linearEqDP(vector<int> &coeff, vector<int> &dp)
{
    dp[0] = 1;
    for (int ele : coeff)
    {
        for (int tar = ele; tar < dp.size(); tar++)
        {
            dp[tar] += dp[tar - ele];
        }
    }
    return dp[dp.size() - 1];
}
int combiFiniteMemo(vector<int> &wt, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == wt.size())
    {
        if (tar == 0)
        {
            return dp[idx][tar] = 1;
        }
        return dp[idx][tar] = 0;
    }
    if (dp[idx][tar] != 0)
        return dp[idx][tar];
    int cnt = 0;
    if (tar - wt[idx] >= 0)
        cnt += combiFiniteMemo(wt, tar - wt[idx], idx + 1, dp);
    cnt += combiFiniteMemo(wt, tar, idx + 1, dp);
    return dp[idx][tar] = cnt;
}
int combiFiniteMemo02(vector<int> &wt, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
        {
            return dp[idx][tar] = 1;
        }
        return dp[idx][tar] = 0;
    }
    if (dp[idx][tar] != 0)
        return dp[idx][tar];
    int cnt = 0;
    if (tar - wt[idx - 1] >= 0)
        cnt += combiFiniteMemo02(wt, tar - wt[idx - 1], idx - 1, dp);
    cnt += combiFiniteMemo02(wt, tar, idx - 1, dp);
    return dp[idx][tar] = cnt;
}
int printPathOfTargetSum(vector<int> &wt, int idx, int tar, string ans, vector<vector<bool>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    if (tar - wt[idx - 1] >= 0 && dp[idx - 1][tar - wt[idx - 1]])
        count += printPathOfTargetSum(wt, idx - 1, tar - wt[idx - 1], ans + to_string(wt[idx - 1]) + " ", dp);

    if (dp[idx - 1][tar])
        count += printPathOfTargetSum(wt, idx - 1, tar, ans, dp);

    return count;
}
void targetSum_02DP(vector<int> &wt, int tar)
{
    vector<vector<bool>> dp(wt.size() + 1, vector<bool>(tar + 1, false));
    int Tar = tar;
    for (int idx = 0; idx <= wt.size(); idx++)
    {
        for (tar = 0; tar <= Tar; tar++)
        {

            if (tar == 0 || idx == 0)
            {
                if (tar == 0)
                    dp[idx][tar] = true;
                continue;
            }

            if (tar - wt[idx - 1] >= 0)
                dp[idx][tar] = dp[idx - 1][tar - wt[idx - 1]];

            dp[idx][tar] = dp[idx][tar] || dp[idx - 1][tar];
        }
    }
    cout << printPathOfTargetSum(wt, wt.size(), Tar, "", dp) << endl;
}

int knapsackMemo(vector<int> &wt, vector<int> &costs, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        return dp[idx][tar] = 0;
    }
    if (dp[idx][tar] != 0)
        return dp[idx][tar];
    int cnt = INT_MIN;
    if (tar - wt[idx - 1] >= 0)
        cnt = max(cnt, knapsackMemo(wt, costs, tar - wt[idx - 1], idx - 1, dp));
    cnt = max(cnt, knapsackMemo(wt, costs, tar, idx - 1, dp));
    return dp[idx][tar] = cnt + costs[idx];
}
int knapsackDP(vector<int> &wt, vector<int> &costs, vector<vector<int>> &dp)
{
    for (int idx = 0; idx < dp.size(); idx++)
    {
        for (int tar = 0; tar < dp[0].size(); tar++)
        {
            if (tar == 0 || idx == 0)
            {
                dp[idx][tar] = 0;
                continue;
            }
            int cnt = INT_MIN;
            if (tar - wt[idx - 1] >= 0)
                cnt = max(cnt, dp[idx - 1][tar - wt[idx - 1]]);
            cnt = max(cnt, dp[idx - 1][tar]);
            dp[idx][tar] = cnt + costs[idx];
        }
    }
    return dp[dp.size() - 1][dp[0].size() - 1];
}
int unboundedKnapDP(vector<int> &costs, vector<int> &wt, vector<int> &dp)
{
    dp[0] = 0;
    for (int i = 0; i < wt.size(); i++)
    {
        for (int tar = wt[i]; tar < dp.size(); tar++)
        {
            dp[tar] = max(dp[tar], dp[tar - wt[i]] + costs[i]);
        }
    }
    return dp[dp.size() - 1];
}
void targetSum()
{
    vector<int> wt = {2, 3, 5, 7};
    int tar = 10;
    // vector<int> dp(tar + 1, 0);
    // vector<vector<int>> dp(wt.size() + 1, vector<int>(tar + 1, 0));

    // cout << combiFiniteDP02(wt, dp) << endl;
    targetSum_02DP(wt, tar);
    // cout<<pathTargetSum(wt,tar,DP.size(),"",DP)<<endl;
    // display2D(dp);
}
// leetcode : 322
// int solve(vector<int> &coins, int amount, vector<int> &dp)
// {
//     if (amount == 0)
//     {
//         return dp[amount] = 1;
//     }
//     if (dp[amount] != -1)
//         return dp[amount];
//     int myAns = INT_MAX;
//     for (int ele : coins)
//     {

//         if (amount - ele >= 0)
//         {
//             int x = solve(coins, amount - ele, dp);
//             if (x != 0)
//                 myAns = min(myAns, x);
//         }
//     }
//     return dp[amount] = (myAns != INT_MAX ? myAns + 1 : 0);
// }
// int coinChange(vector<int> &coins, int amount)
// {
//     vector<int> dp(amount + 1, -1);
//     return solve(coins, amount, dp) - 1;
// }
//===================================LIS===============================================================
vector<int> lisDP(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    // int rv = 0;
    // dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    // display(dp);
    return dp;
}
vector<int> lisR2L(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    // int rv=0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[i])
            {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    return dp;
}
vector<int> ldsL2R(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    // int rv=0;
    for (int i = 1; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[i])
            {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    return dp;
}
vector<int> ldsR2L(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (arr[j] > arr[i])
            {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    return dp;
}
int lbsInverse(vector<int> &arr)
{
    vector<int> dp1 = ldsL2R(arr);
    vector<int> dp2 = ldsR2L(arr);
    int rv = 0;
    for (int i = 0; i < dp1.size(); i++)
    {
        rv = max(rv, dp1[i] + dp2[i] - 1);
    }
    display(dp1);
    cout << endl;
    display(dp2);
    return rv;
}
int lbs(vector<int> &arr)
{
    vector<int> dp1 = lisDP(arr);
    vector<int> dp2 = lisR2L(arr);
    int rv = 0;
    for (int i = 0; i < dp1.size(); i++)
    {
        rv = max(rv, dp1[i] + dp2[i] - 1);
    }
    display(dp1);
    cout << endl;
    display(dp2);

    return rv;
}
vector<int> maxIncSum(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 0);
    dp[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        dp[i] = arr[i];
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], arr[i] + dp[j]);
            }
        }
    }
    return dp;
}
int minDel4Sort(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);
    int rv = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] >= arr[j])
            {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
        rv = max(rv, dp[i]);
    }
    return n - rv;
}
void lisSet()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 14, 6};
    // vector<int> dp1=lisR2L(arr);
    // vector<int> dp2=ldsL2R(arr);
    vector<int> dp = maxIncSum(arr);
    display(dp);
}
//=================================Extras==============================================================
int aIbJcK(string &s)
{
    int acnt = 0, bcnt = 0, ccnt = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'a')
        {
            acnt += 1 + acnt;
        }
        else if(s[i]=='b'){
            bcnt+=acnt+bcnt;
        }
        else{
            ccnt+=bcnt+ccnt;
        }
    }
    return ccnt;
}
void extraSet()
{
    string s="abcabc";
    cout<<aIbJcK(s)<<endl;
}
//=================================Utils===============================================================
void solve()
{
    // coinChange();
    // knapsack();
    // targetSum();
    // mazeSet();
    // fiboSet();
    // minPathSet();
    // pairingProbSet();
    // stringSet();
    // lisSet();
    extraSet();
}
int main()
{
    solve();
}