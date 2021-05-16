import java.util.*;

public class bfsFile {
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

    public static void bfs01(int src, boolean[] vis) { // Cycle Detector
        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(src);
        boolean cycle = false;
        while (!que.isEmpty()) {
            int rVtx = que.removeFirst();
            if (vis[rVtx]) {
                cycle = true;
                continue;
            }
            vis[rVtx] = true;
            for (Edge e : graph[rVtx])
                if (!vis[e.v])
                    que.addLast(e.v);
        }
        System.out.println(cycle);
    }

    public static void bfs02(int src, boolean[] vis) {
        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(src);
        que.addLast(-10);
        boolean cycle = false;
        int level = 0;
        int dest = 6;
        while (que.size() != 1) {
            int rVtx = que.removeFirst();
            if (rVtx == dest) {
                System.out.println(level);
                break;
            }
            if (vis[rVtx]) {
                cycle = true;
                continue;
            }
            vis[rVtx] = true;
            for (Edge e : graph[rVtx])
                if (!vis[e.v])
                    que.addLast(e.v);
            if (que.getFirst() == -10) {
                level++;
                que.addLast(que.removeFirst());
            }
        }
        System.out.println(cycle);
    }

    public static void bfs03(int src, boolean[] vis) {
        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(src);
        boolean cycle = false;
        int level = 0;
        int[] dis = new int[N];
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                int rVtx = que.removeFirst();
                if (vis[rVtx]) {
                    cycle = true;
                    continue;
                }
                dis[rVtx] = level;
                vis[rVtx] = true;
                for (Edge e : graph[rVtx])
                    if (!vis[e.v])
                        que.addLast(e.v);
            }
            level++;
        }
        for (int ele : dis)
            System.out.print(ele + " ");
        System.out.println(cycle);
    }

    public static void bfsDistance(int src, boolean[] vis) { // best for distance not cycle
        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(src);
        boolean cycle = false;
        int dis[] = new int[N];
        int level = 0;
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                int rVtx = que.removeFirst();
                dis[rVtx] = level;
                for (Edge e : graph[rVtx]) {
                    if (!vis[e.v]) {
                        vis[rVtx] = true;
                        que.addLast(e.v);
                    }
                }
            }
        }
        System.out.println(cycle);
    }

    public static class pair {
        int vtx = 0;
        int color = 0;

        pair(int v, int c) {
            this.vtx = v;
            this.color = c;
        }
    }

    public static boolean bipartite(int src, int[] vis) {
        Arrays.fill(vis, -1);
        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(src, 0));
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                pair rVtx = que.removeFirst();
                if (vis[rVtx.vtx] != -1) {
                    if (vis[rVtx.vtx] != rVtx.color) {
                        for (int ele : vis)
                            System.out.print(ele + " ");
                        return false;
                    }
                    continue;
                }
                vis[rVtx.vtx] = rVtx.color;
                for (Edge e : graph[rVtx.vtx]) {
                    if (vis[e.v] != -1)
                        que.addLast(new pair(e.v, 1 - rVtx.color));
                }
            }
        }

        return true;
    }

    public static void solve1() {
        constructGraph();
        // boolean[] vis = new boolean[N];
        // Arrays.fill(vis, false);
        // bfs01(0, vis);
        int[] vis = new int[N];
        System.out.println(bipartite(0, vis));
    }

    public static void main(String[] args) {
        // javac bfsFile.java&&java bfsFile > output.txt
        solve1();
        // solve2();
    }
}
