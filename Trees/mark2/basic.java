import java.util.*;

public class basic {
    public static class Node {
        int data;
        Node left = null;
        Node right = null;

        Node(int k) {
            this.data = k;
        }
    }

    public static int max(Integer... vals) {
        return Collections.max(Arrays.asList(vals));
    }

    static int idx = 0;

    public static Node constructTree(int[] arr) {
        if (idx == arr.length || arr[idx] == -1) {
            idx++;
            return null;
        }
        Node root = new Node(arr[idx++]);
        root.left = constructTree(arr);
        root.right = constructTree(arr);
        return root;
    }

    public static void display(Node root) {
        if (root == null)
            return;
        String str = "";
        str += ((root.left != null) ? root.left.data : ".");
        str += " <- " + root.data + " -> ";
        str += ((root.right != null) ? root.right.data : ".");
        System.out.println(str);
        display(root.left);
        display(root.right);
    }

    public static int size(Node root) {
        if (root == null)
            return 0;
        return size(root.left) + size(root.right) + 1;
    }

    public static int maximum(Node root) {
        if (root == null)
            return (int) (-1e8);
        return max(maximum(root.left), maximum(root.right), root.data);
    }

    public static boolean find(Node root, int k) {
        if (root == null || root.data == k) {
            if (root == null)
                return false;
            return true;
        }
        boolean res = false;
        res = res || find(root.left, k);
        res = res || find(root.right, k);
        return res;
    }

    public static int height(Node root) {
        if (root == null)
            return 0;
        return max(height(root.left), height(root.right)) + 1;
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 40, -1, -1, 50, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1 };
        Node root = constructTree(arr);
        // display(root);
        System.out.println(height(root));
    }
}