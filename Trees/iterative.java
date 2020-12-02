import java.util.*;
public class iterative{
    public class Node{
        int data;
        Node left;
        Node right;
        Node(int d){
            this.data=d;
        }
    }
    public class tpair{
        Node node;
        boolean self;boolean left;boolean right;
        tpair(Node n){
            this.node=n;this.self=false;this.left=false;this.right=false;
        }
    }
    static int idx=0;
    public static Node construct(int[] arr){
        if(arr[idx]==-1||idx>=arr.length){
            idx++;
            return null;
        }
        Node n=new Node(arr[idx++]);
        n.left=construct(arr);
        n.right=construct(arr);
        return n;
    }
    public static void pre(Node root){
        Stack<tpair> st=new Stack<>();
        st.push(new tpair(root));
        while(st.size()!=0){
            tpair top=st.peek();
            if(top.self==false){
                top.self=true;
                System.out.print(top.node.data+" ");
            }
            else if(top.left==false){
                top.left=true;
                if(top.node.left!=null)st.push(new tpair(top.node.left));
            }
            else if(top.right==false){
                top.right=true;
                if(top.node.right!=null)st.push(new tpair(top.node.right));

            }
            else{
                st.pop();
            }
        }
    }
    
    // public static void morrisIn(){
        
    // }
}