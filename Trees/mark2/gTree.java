import java.util.*;

public class gTree {
    public static class Node {
        int data;
        ArrayList<Node> childs;

        Node(int d) {
            this.data = d;
            this.childs = new ArrayList<>();
        }
    }

    public static int max(Integer... vals) {
        return Collections.max(Arrays.asList(vals));
    }

    public static Node construct(int[] arr) {
        Stack<Node> st = new Stack<>();
        for (int i = 0; i < arr.length - 1; i++) {
            if (arr[i] == -1) {
                Node n = st.pop();
                st.peek().childs.add(n);
            } else {
                Node n = new Node(arr[i]);
                st.push(n);
            }
        }
        return st.pop();
    }

    public static void display(Node root) {
        String str = "" + root.data + " -> ";
        for (Node child : root.childs)
            str += child.data + ",";
        System.out.println(str);
        for (Node child : root.childs)
            display(child);
    }

    public static int size(Node root) {
        int rv = 0;
        for (Node child : root.childs)
            rv += size(child);
        return rv + 1;
    }

    public static int height(Node root) {
        int rv = 0;
        for (Node child : root.childs)
            rv = max(height(child), rv);
        return rv + 1;
    }

    public static boolean find(Node root, int d) {
        if (root.data == d)
            return true;
        boolean res = false;
        for (Node child : root.childs)
            res = res || find(child, d);
        return res;
    }

    static ArrayList<Node> n2rpAns = new ArrayList<>();

    public static boolean n2rp(Node root, int d) {
        if (root.data == d) {
            n2rpAns.add(root);
            return true;
        }
        boolean res = false;
        for (Node child : root.childs) {
            res = res || n2rp(child, d);
            if (res) {
                n2rpAns.add(root);
                return true;
            }
        }
        return res;
    }

    public static boolean isFoldable(Node ch1, Node ch2) {
        if (ch1.childs.size() != ch2.childs.size())
            return false;
        for (int i = 0, j = ch2.childs.size() - 1; j >= 0; i++, j--) {
            if (!isFoldable(ch1.childs.get(i), ch2.childs.get(j)))
                return false;
        }
        return true;
    }

    public static boolean isMirror(Node ch1, Node ch2) {
        if (ch1.childs.size() != ch2.childs.size() || ch1.data != ch2.data)
            return false;
        for (int i = 0, j = ch2.childs.size() - 1; i <= j; i++, j--) {
            if (!isMirror(ch1.childs.get(i), ch2.childs.get(j)))
                return false;
        }
        return true;
    }

    public static Node linearize(Node root) {
        int n=root.childs.size();
        if (n == 0)
            return root;
        Node lastTail=linearize(root.childs.get(n-1));
        root.childs.remove(root.childs.size() - 1);
        for (int i = n - 2; i >= 0; i--) {
            Node secondLastTail=linearize(root.childs.get(i));
        
            secondLastTail.childs.add(root.childs.get(i+1));  // connection between two linearize structure.
            
            root.childs.remove(root.childs.size()-1); //remove last node.
        }
        
        return lastTail;
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 30, -1, 40, -1, 50, -1, -1, 60, 70, -1, 80, 90, -1, 100, -1, -1, 110, -1, -1, 120, 130,
                -1, -1, -1 };
        Node root = construct(arr);
        display(root);
    }
}
