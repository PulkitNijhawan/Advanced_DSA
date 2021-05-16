#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

int N;
vector<vector<Edge>> graph;

void addEdge(int u, int v, int w)
{
    graph[u].push_back(Edge(v, w));
    graph[v].push_back(Edge(u, w));
}

void display()
{
    for (int i = 0; i < N; i++)
    {
        cout << (to_string(i) + " -> ");
        for (Edge e : graph[i])
            cout << "(" + to_string(e.v) + ", " + to_string(e.w) + "), ";

        cout << endl;
    }
}

vector<int> par;
vector<int> sizeUF;

int findPar(int u)
{
    if (par[u] == u)
        return u;
    return par[u] = findPar(par[u]);
}

void merge(int p1, int p2)
{
    if (sizeUF[p1] < sizeUF[p2])
    {
        par[p1] = p2;
        sizeUF[p2] += sizeUF[p1];
    }
    else
    {
        par[p2] = p1;
        sizeUF[p1] += sizeUF[p2];
    }
}

void unionFind(int n, vector<vector<int>> &edges)
{
    for (int i = 0; i < n; i++)
    {
        par.push_back(i);
        sizeUF.push_back(1);
    }

    for (vector<int> a : edges) // a = {u,v,w};
    {
        int gp1 = findPar(a[0]); // par of u
        int gp2 = findPar(a[1]); // par of v

        if (gp1 != gp2)
        {
            merge(gp1, gp2);
            addEdge(a[0], a[1], a[2]);
        }
    }
}

void KruskalAlgo(int NoOfVertex, vector<vector<int>> &edges)
{
    graph.resize(NoOfVertex, vector<Edge>());

    sort(edges.begin(), edges.end(), [](auto a, auto b) {
        return a[2] < b[2];
    });

    unionFind(NoOfVertex, edges);

    display();
}
int waterDistributionProblemSolve(int n, vector<vector<int>> &pipes)
{
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        par.push_back(i);
        sizeUF.push_back(1);
    }
    for (vector<int> &a : pipes)
    {
        int gp1 = findPar(a[0]);
        int gp2 = findPar(a[1]);
        if (gp1 != gp2)
        {
            ans += a[2];
            par[gp2] = gp1;
            sizeUF[gp1] += sizeUF[gp2];
        }
    }
    return ans;
}
void waterDistributionProblem()
{
    int n = 3;
    vector<int> wells{1, 2, 2};
    vector<vector<int>> pipes{{1, 2, 3}, {2, 3, 1}};
    for (int i = 0; i < n; i++)
    {
        pipes.push_back({0, i + 1, wells[i]});
    }
    sort(pipes.begin(), pipes.end(), [](auto a, auto b) {
        return a[2] < b[2];
    });
    waterDistributionProblemSolve(n, pipes);
}

int main()
{
    N = 9;
    vector<vector<int>> edges = {{0, 1, 4}, {0, 7, 8}, {1, 7, 11}, {1, 2, 8}, {7, 8, 7}, {7, 6, 1}, {2, 8, 2}, {8, 6, 6}, {2, 5, 4}, {2, 3, 7}, {6, 5, 2}, {3, 4, 9}, {3, 5, 14}, {5, 4, 10}};
    KruskalAlgo(9, edges);
    return 0;
}