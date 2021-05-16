#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef pair<int, int> pii;
typedef long long ll;
template <typename T>
void print(vector<T> &arr)
{
    for (T ele : arr)
        cout << ele << " ";
    cout << "\n";
}
template <typename T>
void print2d(vector<vector<T>> &arr)
{
    for (auto &ar : arr)
    {
        print(ar);
    }
    cout << "\n";
}
int n, m;
vvi dirA{{1, 0}, {0, 1},{0,-1},{-1,0}};
void dfs(int r, int c, vector<vector<char>> &graph, int ans)
{
    graph[r][c] = '&';
    for (unsigned int d = 0; d < dirA.size(); d++)
    {
        int x = r + dirA[d][0];
        int y = c + dirA[d][1];
        if (x >= 0 && y >= 0 && x < n && y < m && graph[x][y] == '.')
            dfs(x, y, graph, ans);
    }
}
int main()
{

    cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> graph[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (graph[i][j] == '.')
            {
                ans++;
                dfs(i, j, graph, ans);
            }
        }
    }
    // print2d(graph);
    cout << ans;
    return 0;
}