#include <iostream>
#include <vector>
#include <list>
using namespace std;
#define mod 1000000007
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vi> vvi;
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
class Edge
{
public:
    int v = 0;
    int w = 0;
    Edge(int v, int w)
    {
        this->v = v;
        this->w = w;
    }
};
int N = 7;
vector<vector<Edge>> graph(N, vector<Edge>());
void addEdge(int u, int v, int w)
{
    graph[u].push_back(Edge(v, w));
    graph[v].push_back(Edge(u, w));
}
void constructGraph()
{

    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 8);
    addEdge(5, 6, 3);
}
void display()
{
    for (int i = 0; i < N; i++)
    {
        cout << to_string(i) << "-> ";
        for (Edge e : graph[i])
        {
            cout << "(" << to_string(e.v) << "," << to_string(e.w) << ") ";
        }
        cout << "\n";
    }
}

int main()
{
    // g++ l01.cpp -o p&&./p > output.txt
    constructGraph();
    display();
}