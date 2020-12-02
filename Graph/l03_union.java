import java.util.*;
public class l03_union {
    static int[] size;
    static int[]  par;
    static int N=8;
    public static int findPar(int p){
        if(par[p]==p)return p;
        return par[p]=findPar(p);
    }
    public static void merge(int p1,int p2){
        if(size[p1]<size[p2]){
            par[p1]=p2;
            size[p2]+=size[p1];
        }
        else{
            par[p2]=p1;
            size[p1]+=size[p2];
        }
    }
    public static void addEdge(ArrayList<Integer>[] graph,int u,int v){
        graph[u].add(v);graph[v].add(u);
    }
    public static void unionFind(int[][] edges){
        for(int i=0;i<N;i++){
            size[i]=1;
            par[i]=i;
        }
        ArrayList<Integer>[] graph=new ArrayList[N];
        for(int[] e:edges){
            int p1=findPar(e[0]);
            int p2=findPar(e[1]);
            if(p1!=p2){
                merge(p1,p2);
                addEdge(graph,e[0],e[1]);
            }
        }

    }

    public static void main(String[] args){

    }
}