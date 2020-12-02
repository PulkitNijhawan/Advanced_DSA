import java.util.ArrayList;
import java.util.LinkedList;
public class directed {
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
        // addEdge(2, 6, 4);
    }
    public static void topologicalSort(int src,boolean[] vis,ArrayList<Integer> ans){
        vis[src]=true;
        for(Edge e:graph[src]){
            if(!vis[e.val])topologicalSort(e.val, vis, ans);
        }
        ans.add(src);

    }
    public static void topological(){
        boolean[] vis=new boolean[N];

        ArrayList<Integer> ans=new ArrayList<>();
        for(int i=0;i<N;i++){
            if(!vis[i])topologicalSort(i,vis,ans);
        }
        for(int i=ans.size()-1;i>=0;i--){
            System.out.print(ans.get(i)+" ");
        }
        System.out.println();
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
    public static void main(String[] args){
        constructGraph();
        display();
        topological();
    }
}