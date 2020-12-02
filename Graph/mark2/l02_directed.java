import java.util.*;

public class l02_directed {
    public static class Edge {
        int val;
        int w;

        Edge(int V, int W) {
            this.val = V;
            this.w = W;
        }
    }

    static int N = 7;
    static ArrayList<Edge>[] graph = new ArrayList[N];

    public static void addEdge(int u, int v, int w) {
        graph[u].add(new Edge(v, w));
    }

    public static void constructGraph() {
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<Edge>();
        }
        addEdge(0, 1, 20);
        addEdge(0, 3, 10);
        addEdge(1, 2, 10);
        addEdge(2, 3, 40);
        addEdge(3, 4, 2);
        addEdge(4, 5, 2);
        addEdge(4, 6, 3);
        addEdge(5, 6, 8);
        addEdge(2, 0, 4);
    }

    public static void dfs_topo(int src, ArrayList<Integer> st, boolean[] vis) {
        vis[src] = true;
        for (Edge e : graph[src]) {
            if (!vis[e.val])
                dfs_topo(e.val, st, vis);
        }
        st.add(src);
    }

    public static void topologicalSort(ArrayList<Integer> st, boolean[] vis) {

        for (int i = 0; i < N; i++) {
            if (!vis[i])
                dfs_topo(i, st, vis);
        }
        for (int i = st.size() - 1; i >= 0; i--) {
            System.out.print(st.get(i) + " ");
        }
    }

    public static void kahnsAlgo() {
        LinkedList<Integer> que = new LinkedList<>();
        int[] indegree = new int[N];
        for (int i = 0; i < N; i++) {
            for (Edge e : graph[i]) {
                indegree[e.val]++;
            }
        }
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < N; i++)
            if (indegree[i] == 0)
                que.addLast(i);
        while (que.size() != 0) {
            int rvtx = que.removeFirst();
            ans.add(rvtx);
            for (Edge e : graph[rvtx]) {
                if (--indegree[e.val] == 0)
                    que.addLast(e.val);
            }
        }
        if (ans.size() != N)
            ans.clear();
        for (int i = 0; i < ans.size(); i++) {
            System.out.print(ans.get(i) + " ");
        }

    }

    public static boolean dfs(int src, int[] check) {
        check[src] = 2;
        boolean ans = false;
        for (Edge e : graph[src]) {
            if (check[e.val] == 0)
                ans = ans || dfs(e.val, check);
            else if (check[e.val] == 2) {
                return true;
            }
        }
        check[src] = 1;
        return ans;
    }

    public static void dfsCycle() {
        int[] check = new int[N];
        boolean ans = false;
        for (int i = 0; i < N; i++) {
            if (check[i] == 0)
                ans = ans || dfs(i, check);
        }
        System.out.print(ans);
    }

    public static void main(String[] args) {
        constructGraph();
        boolean[] vis = new boolean[N];
        ArrayList<Integer> st = new ArrayList<>();
        // topologicalSort(st, vis);
        // kahnsAlgo();
        dfsCycle();
    }
}