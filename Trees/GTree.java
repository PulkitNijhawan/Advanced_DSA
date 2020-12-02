import java.util.*;
public class GTree{
    public static class Node{
        int data;
        ArrayList<Node> childs;
        Node(int d){
            this.data=d;
            this.childs=new ArrayList<>();
        }
    }
    
    public static Node construct(int[] arr){
        Stack<Node> st=new Stack<>();
        for(int i=0;i<arr.length;i++){
            if(arr[i]==-1){
                Node n=st.pop();
                st.peek().childs.add(n);
            }
            else{
                Node n=new Node(arr[i]);
                st.push(n);
            }
        }
        return st.pop();
    }
    public static void display(Node root){
        System.out.print(root.data+" -> ");
        for(Node c:root.childs){
            System.out.print(c.data+" ");
        }
        System.out.println();
        for(Node c:root.childs){
            display(c);
        }
    }
//=============================Basic=======================================================
    public static int size(Node root){
        int s=0;
        for(Node c:root.childs){
            s+=size(c);
        }
        return s+1;
    }
    public static int height(Node root){
        int h=0;
        for(Node c:root.childs){
            h=Math.max(h,height(c));
        }
        return h;
    }
    public static boolean find(Node root,int key){
        boolean res=false;
        if(root.data==key)res=true;
        for(Node c:root.childs){
            res=res||find(c, key);
        }
        return res;
    }
//================================Paths========================================================
    public static boolean n2rp(Node root,ArrayList<Node> path,int data){
        path.add(root);
        if(root.data==data){
            return true;
        }
        boolean res=false;
        for(Node c:root.childs){
            res=res||n2rp(c,path,data);
        }
        if(res==false)path.remove(path.size()-1);
        return res;
    }
//===============================BFS===============================================================
    public static void levelOrder(Node root){
        LinkedList<Node> que=new LinkedList<>();
        que.addLast(root);
        while(que.size()!=0){
            int size=que.size();
            while(size-->0){
                Node curr=que.removeFirst();
                System.out.print(curr.data+" ");
                for(Node c:curr.childs){
                    que.addLast(c);
                }
            }
            System.out.println();
        }
    }
    public static Node linearize(Node root){
        if(root.childs.size()==0)return root;
        int n=root.childs.size();
        Node returnTail=linearize(root.childs.get(childs.size()-1));
        for(int i=n-2;i>=0;i--){
            Node secondLast=linearize(childs.get(i));
            secondLast.childs.add(root.childs.get(i+1));
            root.childs.remove(root.childs.size()-1);
        }
        return returnTail;
    }
}