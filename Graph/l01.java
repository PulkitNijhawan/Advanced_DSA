import java.util.*;

public class l01 {
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
        graph[v].add(new Edge(u, w));
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
        // addEdge(2, 6, 4);
    }

    public static int findEdge(int u, int v) {
        for (int i = 0; i < graph[u].size(); i++) {
            Edge e = graph[u].get(i);
            if (e.val == v)
                return i;
        }

        return -1;
    }

    public static void removeEdge(int u, int v) {
        int uv = findEdge(u, v);
        int vu = findEdge(v, u);
        graph[u].remove(uv);
        graph[v].remove(vu);
    }

    public static void display() {
        for (int i = 0; i < N; i++) {
            System.out.print(i + " -> ");
            for (Edge e : graph[i]) {
                System.out.print("(" + e.val + "," + e.w + ") ");
            }
            System.out.println();
        }
    }

    public static void removeVtx(int vtx) {
        while (graph[vtx].size() != 0) {
            int temp = graph[vtx].get(graph[vtx].size() - 1).val;
            removeEdge(vtx, temp);
        }
    }

    public static boolean hasPath(int s, int d, boolean[] vis) {
        if (s == d)
            return true;
        boolean res = false;
        vis[s] = true;
        for (Edge e : graph[s]) {
            if (!vis[e.val])
                res = res || hasPath(e.val, d, vis);
        }
        return res;
    }

    public static int allPath(int s, int d, boolean[] vis, String path, int cost) {
        if (s == d) {
            System.out.println(path + d + " @" + cost);
            return 1;
        }
        vis[s] = true;
        int cnt = 0;
        for (Edge e : graph[s]) {
            if (!vis[e.val])
                cnt += allPath(e.val, d, vis, path + s + " ", cost + e.w);
        }
        vis[s] = false;
        return cnt;
    }
    // public static int minPath(){
    // if(s==d){

    // }
    // vis[s] = true;
    // int rv=1e8;
    // for (Edge e : graph[s]) {
    // if (!vis[e.val])
    // rv=Math.min(rv,minPath()+e.w);
    // }
    // vis[s] = false;
    // return rv;
    // }
    static int ceil = (int) 1e8;
    static int floor = (int) -1e8;

    public static void ceil_floor(int src, int des, int key, boolean[] vis, int cost) {
        if (src == des) {
            if (cost < key) {
                floor = Math.max(floor, cost);
            }
            if (cost > key) {
                ceil = Math.min(ceil, cost);
            }
            return;
        }
        vis[src] = true;
        for (Edge e : graph[src]) {
            if (!vis[e.val])
                ceil_floor(e.val, des, key, vis, cost + e.w);
        }
        vis[src] = false;
    }

    public static boolean hamiltonionCycle(int src, int osrc, boolean[] vis, String path, int count) {
        if (count == N - 1) {
            System.out.println(path+src);
            if (findEdge(src, osrc) == -1)
                return false;
            else
                return true;
        }
        vis[src] = true;
        boolean res = false;
        for (Edge e : graph[src]) {
            if (!vis[e.val])
                res = res || hamiltonionCycle(e.val, osrc, vis, path + src+" ", count + 1);
        }
        vis[src] = false;
        return res;
    }
    public static void gcc(int src,boolean[] vis){
        vis[src]=true;
        for(Edge e:graph[src]){
            if(!vis[e.val])gcc(e.val,vis);
        }
    }
    public static class bfsHelper{
        int v;
        String path;
        bfsHelper(int v,String p){
            this.v=v;this.path=p;
        }
    }
    public static int bfs(int src,boolean[] vis){
        int cycle=0;
        LinkedList<bfsHelper> que=new LinkedList<>();
        que.add(new bfsHelper(src,""+src));
        while(que.size()!=0){
            bfsHelper vtx=que.removeFirst();
            if(vis[vtx.v]){
                cycle++;
                System.out.println(vtx.path);
                continue;
            }
            vis[vtx.v]=true;
            for(Edge e:graph[vtx.v]){
                if(!vis[e.val])que.addLast(new bfsHelper(e.val,vtx.path+e.val));
            }
        }
        return cycle;
    }
    public class pair{
        int v;String psf;int level;
        pair(int v,String s,int l){
            this.v=v;this.psf=s;this.level=l;
        }
    }
    public static void bfs02(int src,boolean[] vis){
        LinkedList<pair> que=new LinkedList<>();
        que.addLast(new pair(src,""+src,0));
        while(que.size()!=0){
            pair rvtx=que.removeFirst();
            if(vis[rvtx.v]){
                System.out.println("Cycle:"+rvtx.psf);
                continue;
            }
            vis[rvtx.v]=true;
            for(Edge e:graph[rvtx.v]){
                if(!vis[e.val])que.addLast(new pair(e.val,rvtx.psf+e.val,rvtx.level+1));
            }
        }
    }
    public static boolean bipartite(int src){
        int[] vis=new int[N];
        LinkedList<int[]> que=new LinkedList<>();
        que.addLast(new int[]{src,0});
        while(que.size()!=0){
            int size=que.size();
            while(size-->0){
                int[] pair=que.removeFirst();
                int rvtx=pair[0];
                int color=pair[1];
                if(vis[rvtx]!=-1){
                    if(color!=vis[rvtx])return false;
                    continue;
                }
                vis[rvtx]=color;
                for(Edge e:graph[rvtx]){
                    if(vis[e.val]!=-1){
                        que.addLast(new int[]{e.val,(color+1)%2});
                    }
                }
            }
        }
        return true;

    }

    public static void main(String[] args) {
        boolean[] vis = new boolean[N];
        constructGraph();
        // display();
        // ceil_floor(0, 6, 30, vis, 0);
        // System.out.println(hasPath(0, 6, vis));
        // System.out.println(ceil+" "+ floor);
        // int gccCnt=0;
        // for(int i=0;i<N;i++){
        //     if(!vis[i]){
        //         gcc(i,vis);
        //         gccCnt++;
        //     }
        // }
        // // System.out.println(hamiltonionCycle(2, 2, vis, "", 0));
        // System.out.println(gccCnt);
        System.out.println(bfs(0,vis)); 
    }

}