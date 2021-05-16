import java.util.*;

public class dijkstraAndPrims {

    public static class Edge {
        int v = 0;
        int w = 0;

        public Edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    public static void addEdge(ArrayList<Edge>[] graph, int u, int v, int w) {
        graph[u].add(new Edge(v, w));
        graph[v].add(new Edge(u, w));
    }

    public static void display(ArrayList<Edge>[] graph, int N) {
        for (int i = 0; i < N; i++) {
            System.out.print(i + " -> ");
            for (Edge e : graph[i]) {
                System.out.print("(" + e.v + ", " + e.w + "), ");
            }

            System.out.println();
        }
    }

    public static class primsPair {
        int par = 0;
        int vtx = 0;
        int w = 0;

        primsPair(int vtx, int par, int w) {
            this.par = par;
            this.vtx = vtx;
            this.w = w;
        }
    }

    public static void primsAlgo(ArrayList<Edge>[] graph, int N) {
        @SuppressWarnings("unchecked")
        ArrayList<Edge>[] ngraph = new ArrayList[N];
        for (int i = 0; i < N; i++)
            ngraph[i] = new ArrayList<>();

        boolean[] vis = new boolean[N];
        PriorityQueue<primsPair> que = new PriorityQueue<>((a, b) -> {
            return a.w - b.w; // this - other
        });

        que.add(new primsPair(0, -1, 0));

        int EdgesCount = 0;
        while (EdgesCount <= N - 1) {
            primsPair pair = que.remove();

            if (vis[pair.vtx])
                continue;

            if (pair.par != -1) {
                addEdge(ngraph, pair.par, pair.vtx, pair.w);
                EdgesCount++;
            }

            vis[pair.vtx] = true;
            for (Edge e : graph[pair.vtx]) {
                if (!vis[e.v]) {
                    que.add(new primsPair(e.v, pair.vtx, e.w));
                }
            }
        }

        display(ngraph, N);
    }

    public static class dijkstraPair {
        int vtx = 0;
        int par = 0;
        int wsf = 0;

        dijkstraPair(int vtx, int par, int wsf) {
            this.vtx = vtx;
            this.par = par;
            this.wsf = wsf;
        }
    }

    public static void dijkstraAlgo(ArrayList<Edge>[] graph, int N) {
        boolean[] vis = new boolean[N];
        PriorityQueue<dijkstraPair> que = new PriorityQueue<>((a, b) -> {
            return a.wsf - b.wsf; // this - other
        });
        int[] dis = new int[N];
        int[] par = new int[N];
        Arrays.fill(dis, (int) 1e8);
        Arrays.fill(par, -1);
        que.add(new dijkstraPair(0, -1, 0));
        dis[0] = 0;
        int EdgesCount = 0;
        while (EdgesCount <= N - 1) {
            dijkstraPair pair = que.remove();
            if (vis[pair.vtx]) 
                continue;
            if (pair.par != -1)
                EdgesCount++;
            vis[pair.vtx] = true;
            par[pair.vtx] = pair.par;
            for (Edge e : graph[pair.vtx]) {
                if (!vis[e.v] && pair.wsf + e.w < dis[e.v]) {
                    dis[e.v] = pair.wsf + e.w;
                    que.add(new dijkstraPair(e.v, pair.vtx, pair.wsf + e.w));
                }
            }
        }
    }
}