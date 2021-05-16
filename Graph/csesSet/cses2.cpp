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
template <typename T>
void intput(vector<T> &arr, int n)
{
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}
template <typename T>
void input2d(vector<vector<T>> &arr, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
}
// cd C:/Users/pulki/Desktop
// g++ name.cpp -o p&&./p < input.txt > output.txt

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));
    input2d(graph, n, m);
    int start;
    pii end;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (graph[i][j] == 'A')
            {
                start = i * m + j;
                break;
            }
        }
    }
    vvi vis(n,vi(m,0));
    list<pair<int, string>> que;
    que.push_back({start, ""});
    vis[start/m][start%m]=1;
    vvi dirA{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    vs dirS{"R", "L", "U", "D"};
    while (!que.empty())
    {
        pair<int, string> rem = que.front();
        que.pop_front();
        for (unsigned int d = 0; d < dirA.size(); d++)
        {
            int x = (rem.first / m) + dirA[d][0];
            int y = (rem.first % m) + dirA[d][1];

            if (x >= 0 && y >= 0 && x < n && y < m && (graph[x][y] =='.'||graph[x][y]=='B')&&!vis[x][y])
            {
                if (graph[x][y] == 'B')
                {
                    cout << "YES"<< "\n";
                    
                    cout << rem.second.length()+1 << "\n";
                    cout<<rem.second<<dirS[d];
                    return 0;
                }
                vis[x][y] = 1;
                que.push_back({x * m + y, rem.second + dirS[d]});
            }
        }
    }
    // print2d(graph);
    cout << "NO";
    return 0;
}