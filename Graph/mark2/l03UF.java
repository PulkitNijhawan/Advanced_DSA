import java.util.*;
public class l03UF {
    static int[] par;
    static int[] size;
    // static int N=7;
    static ArrayList<Integer>[] graph=new ArrayList[N];
    public static void addEdge(int u, int v) {
        graph[u].add(v);
        graph[v].add(u);
    }
    public static int findPar(int u){
        if(par[u]==u)return u;
        return par[u]=findPar(par[u]);
    }
    public static void merge(int p1,int p2){
        if(size[p1]>size[p2]){
            par[p2]=p1;
            size[p1]+=size[p2];
        }
        else{
            par[p1]=p2;
            size[p2]+=size[p1];
        }
    }
    public static void unionFind(int[][] edges,int N){
        
        Arrays.fill(graph,new ArrayList<>());
        par=new int[N];
        size=new int[N];
        for(int i=0;i<N;i++){
            par[i]=i;
            size[i]=1;
        }
        for(int[] e:edges){
            int u=e[0];
            int v=e[1];
            int p1=findPar(u);
            int p2=findPar(v);
            if(p1!=p2){
                merge(p1,p2);
                addEdge(u, v);
            }
        }
    }
}
