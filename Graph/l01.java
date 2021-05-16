import java.util.*;

public class l01 {
    public static int max(Integer... vals) {
        return Collections.max(Arrays.asList(vals));
    }

    public static class Edge {
        int v = 0;
        int w = 0;

        Edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    static int N = 7;
    @SuppressWarnings("unchecked")
    static ArrayList<Edge>[] graph = new ArrayList[N];

    public static void addEdge(int u, int v, int w) {
        graph[u].add(new Edge(v, w));
        graph[v].add(new Edge(u, w));
    }

    public static void constructGraph() {
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<Edge>();
        }
        addEdge(0, 1, 10);
        addEdge(0, 3, 10);
        addEdge(1, 2, 10);
        addEdge(2, 3, 40);
        addEdge(3, 4, 2);
        addEdge(4, 5, 2);
        addEdge(4, 6, 8);
        addEdge(5, 6, 3);
        // addEdge(2, 5, 6);
    }

    public static void display() {
        for (int i = 0; i < N; i++) {
            System.out.print(i + "-> ");
            for (Edge e : graph[i]) {
                System.out.print("(" + e.v + "," + e.w + ") ");
            }
            System.out.println();
        }
    }

    public static int searchVtx(int u, int v) {
        for (int i = 0; i < graph[u].size(); i++) {
            Edge e = graph[u].get(i);
            if (e.v == v)
                return i;
        }
        return -1;
    }

    public static void removeVtx(int u) {
        for (int i = graph[u].size() - 1; i >= 0; i--) {
            Edge e = graph[u].get(i);
            removeEdge(u, e.v);
        }
    }

    public static void removeEdge(int u, int v) {
        graph[u].remove(searchVtx(u, v));
        graph[v].remove(searchVtx(v, u));
    }

    public static boolean hasPath(int src, int dest, boolean[] visited) {
        if (src == dest)
            return true;
        visited[src] = true;
        boolean tendency = false;
        for (Edge e : graph[src]) {
            if (!visited[e.v])
                tendency = tendency || hasPath(e.v, dest, visited);
        }
        return tendency;
    }

    public static int allPath(int src, int dest, boolean[] visited, String path, int wsf) {
        if (src == dest) {
            System.out.println(path + "@ " + wsf);
            return 1;
        }
        visited[src] = true;
        int tendency = 0;
        for (Edge e : graph[src]) {
            if (!visited[e.v])
                tendency += allPath(e.v, dest, visited, path + e.v + " ", wsf + e.w);
        }
        visited[src] = false;
        return tendency;
    }

    public static class pathHelper {
        int weight = 0;
        String path = "";

        pathHelper(int w, String p) {
            this.weight = w;
            this.path = p;
        }
    }

    public static pathHelper minPath(int src, int dest, boolean[] visited, String path, int wsf) {
        if (src == dest) {
            return new pathHelper(wsf, path + "@ " + wsf);
        }
        pathHelper tendency = new pathHelper((int) 1e8, "");
        visited[src] = true;
        for (Edge e : graph[src]) {
            if (!visited[e.v]) {
                pathHelper recAns = minPath(e.v, dest, visited, path + e.v + " ", wsf + e.w);
                if (recAns.weight < tendency.weight)
                    tendency = recAns;
            }

        }
        visited[src] = false;
        return tendency;
    }

    public static pathHelper maxPath(int src, int dest, boolean[] visited, String path, int wsf) {
        if (src == dest) {
            return new pathHelper(wsf, path + "@ " + wsf);
        }
        pathHelper tendency = new pathHelper(-(int) 1e8, "");
        visited[src] = true;
        for (Edge e : graph[src]) {
            if (!visited[e.v]) {
                pathHelper recAns = maxPath(e.v, dest, visited, path + e.v + " ", wsf + e.w);
                if (recAns.weight > tendency.weight)
                    tendency = recAns;
            }

        }
        visited[src] = false;
        return tendency;
    }

    public static int hamiltonianPath(int src, int osrc, int edgeCnt, boolean[] visited, String path) {
        if (edgeCnt == N - 1) {
            if (searchVtx(src, osrc) != -1)
                System.out.println("Cycle: " + path);
            else
                System.out.println("Path: " + path);
            return 1;
        }
        visited[src] = true;
        int tendency = 0;
        for (Edge e : graph[src]) {
            if (!visited[e.v])
                tendency += hamiltonianPath(e.v, osrc, edgeCnt + 1, visited, path + e.v + " ");
        }
        visited[src] = false;
        return tendency;
    }

    public static void dfs(int src, boolean[] visited) {
        visited[src] = true;
        for (Edge e : graph[src]) {
            if (!visited[e.v])
                dfs(e.v, visited);
        }
    }

    public static int gcc(boolean[] visited) {
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                ans++;
                dfs(i, visited);
            }
        }
        return ans;
    }

    static int[][] dirA = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

    public static int parameterIsland(int i, int j, int[][] arr) {
        // Leetcode: 463
        arr[i][j] = -2;
        int nbrs = 0;
        int rv = 0;
        for (int d = 0; d < dirA.length; d++) {
            int x = i + dirA[d][0];
            int y = j + dirA[d][1];
            if (x >= 0 && y >= 0 && x < dirA.length && y < dirA[0].length && arr[x][y] == 1) {
                nbrs++;
                rv += parameterIsland(x, y, arr);
            }
        }
        return rv + nbrs; // returning nbrs
    }
    
    public static void solve1() {
        constructGraph();
        // removeVtx(4);
        boolean[] visited = new boolean[N];
        Arrays.fill(visited, false);
        // removeEdge(3, 4);
        // System.out.println(hasPath(0, 6, visited) + "\n");
        System.out.println(allPath(0, 6, visited, "" + 0 + " ", 0));
        // for(boolean b:visited){
        // System.out.print(b+" ");
        // }
        // System.out.println(maxPath(0, 6, visited, ""+0+" ", 0).path);
        // display();
    }

    public static void solve2() {
        constructGraph();
        boolean[] visited = new boolean[N];
        Arrays.fill(visited, false);
        // System.out.println(hamiltonianPath(0, 0, 0, visited, ""+0+ " "));
        removeEdge(3, 4);
        System.out.println(gcc(visited));
    }

    public static void main(String[] args) {
        // javac l01.java&&java l01 > output.txt
        // solve1();
        solve2();
    }
}