import java.util.*;

public class lo1 {
    static class Node {
        int data;
        Node left;
        Node right;

        Node(int d) {
            this.data = d;
        }

        Node() {
            this.data = -1;
            this.left = null;
            this.right = null;
        }
    }

    static int idx = 0;

    public static Node construct(int[] arr) {
        if (idx >= arr.length || arr[idx] == -1) {
            idx++;
            return null;
        }
        Node n = new Node(arr[idx++]);
        n.left = construct(arr);
        n.right = construct(arr);
        return n;
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
    // ============================Basic=============================================================

    public static int size(Node root) {
        if (root == null)
            return 0;
        return size(root.left) + size(root.right) + 1;
    }

    public static int height(Node root) {
        if (root == null) {
            return -1; // -1 for edges terms
        }
        return Math.max(height(root.left), height(root.right)) + 1;
    }

    public static boolean find(Node root, int k) {
        if (root == null)
            return false;
        if (root.data == k)
            return true;
        return find(root.left, k) || find(root.right, k);
    }

    public static int max(Node root) {
        if (root == null) {
            return (int) -10e8;
        }
        return Math.max(max(root.right), Math.max(max(root.left), root.data));
    }

    public static int min(Node root) {
        if (root == null)
            return (int) 1e8;
        return Math.min(min(root.right), Math.min(min(root.left), root.data));
    }

    // =============================Paths==============================================================
    public static boolean n2rp(Node root, int k, ArrayList<Node> path) {
        if (root == null)
            return false;
        if (root.data == k) {
            path.add(root);
            return true;
        }
        if (n2rp(root.left, k, path) || n2rp(root.right, k, path))
            path.add(root);
        return n2rp(root.left, k, path) || n2rp(root.right, k, path);
    }

    public static ArrayList<Node> n2rp02(Node root, int k) {
        if (root == null) {
            return new ArrayList<>();
        }
        if (root.data == k) {
            ArrayList<Node> base = new ArrayList<>();
            base.add(root);
            return base;
        }
        ArrayList<Node> left = n2rp02(root.left, k);
        if (left.size() != 0) {
            left.add(root);
            return left;
        }
        ArrayList<Node> right = n2rp02(root.right, k);
        if (right.size() != 0) {
            right.add(root);
            return right;
        }
        return new ArrayList<>();

    }

    static Node LCA = null;

    public static boolean lca02(Node root, int a, int b) {
        if (root == null)
            return false;
        boolean myAns = false;
        if (root.data == a || root.data == b) {
            myAns = true;
        }

        boolean left = lca02(root.left, a, b);
        if (LCA != null)
            return true;
        boolean right = lca02(root.right, a, b);
        if (LCA != null)
            return true;// basically stopping post work
        if ((myAns && left) || (myAns && right) || (right && left)) {
            LCA = root;
            return true;
        }
        return myAns || left || right;
    }

    public static void kDown(Node root, int k, Node block) {
        if (root == null || root == block)
            return;
        if (k == 0) {
            System.out.print(root.data + " ");
            return;
        }
        kDown(root.left, k - 1, block);
        kDown(root.right, k - 1, block);

    }

    public static void kFar(Node root, int tar, int k) {
        ArrayList<Node> path = new ArrayList<>();
        boolean ans = n2rp(root, k, path);
        Node block = null;
        for (int i = 0; i < path.size(); i++) {
            if (k - i < 0)
                break;
            kDown(root, k - i, block);
            block = path.get(i);
        }
    }

    public static int kFar02(Node root, int tar, int k) {
        if (root == null)
            return -1;
        if (root.data == tar) {
            kDown(root, k, null);
            return 1;
        }
        int leftDis = kFar02(root, tar, k);
        if (leftDis != -1) {
            kDown(root, k - leftDis, root.left);
            return leftDis + 1;
        }
        int rightDis = kFar02(root, tar, k);
        if (rightDis != -1) {
            kDown(root, k - rightDis, root.right);
            return rightDis + 1;
        }
        return -1;
    }

    public static void kDown01(Node root, int k) {
        if (root == null)
            return;
        if (k == 0) {
            System.out.print(root.data + " ");
            return;
        }
        kDown01(root.left, k - 1);
        kDown01(root.right, k - 1);
    }

    public static int kFar03(Node root, int tar, int k) {
        if (root == null)
            return -1;
        if (root.data == tar) {
            kDown01(root, k);
            return 1;
        }
        int left = kFar03(root.left, tar, k);
        if (left != 0) {
            if (k - left == 0)
                System.out.print(root.data + " ");
            else
                kDown01(root.right, k - left - 1);
            return left + 1;
        }
        int right = kFar03(root.right, tar, k);
        if (right != 0) {
            if (k - right == 0)
                System.out.print(root.data + " ");
            else
                kDown01(root.left, k - right - 1);
            return right + 1;
        }
        return -1;
    }

    static int ans = Integer.MIN_VALUE;

    public static int leaf2leafSum(Node root) {
        if (root == null)
            return (int) -1e8;
        int left = leaf2leafSum(root.left);
        int right = leaf2leafSum(root.right);
        if (root.right != null && root.left != null) {
            ans = Math.max(ans, left + right + root.data);
            return Math.max(left, right) + root.data;
        }
        return (root.right != null ? right : left) + root.data;
    }

    // ============================BFS============================================
    public static void levelOrder(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        que.addLast(null);
        int cnt = 0;
        System.out.print("Level:" + cnt + " -> ");
        while (que.size() != 0) {
            Node curr = que.removeFirst();
            if (curr == null) {
                System.out.println();
                System.out.print("Level:" + ++cnt + " -> ");
                if (que.size() != 0)
                    que.addLast(null);
            } else {
                System.out.print(curr.data + " ");
                if (curr.left != null)
                    que.addLast(curr.left);
                if (curr.right != null)
                    que.addLast(curr.right);
            }
        }
    }

    public static void levelOrder02(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        int count = 0;
        while (que.size() != 0) {

            int size = que.size();
            System.out.print("Level: " + count + " -> ");
            count++;
            while (size-- > 0) {
                Node curr = que.removeFirst();
                System.out.print(curr.data + " ");
                if (curr.left != null)
                    que.addLast(curr.left);
                if (curr.right != null)
                    que.addLast(curr.right);
            }
            System.out.println();

        }
    }

    public static void levelOrder03(Node root) {
        LinkedList<Node> par = new LinkedList<>();
        LinkedList<Node> child = new LinkedList<>();
        par.addLast(root);

        int cnt = 0;
        System.out.print("Level:" + cnt++ + " -> ");
        while (par.size() != 0) {

            Node curr = par.removeFirst();
            if (curr.left != null)
                child.addLast(curr.left);
            if (curr.right != null)
                child.addLast(curr.right);
            System.out.print(curr.data + " ");
            if (par.size() == 0) {
                LinkedList<Node> temp = par;
                par = child;
                child = temp;
                System.out.print("\nLevel:" + cnt++ + " -> ");
            }
        }
    }

    public static void leftView(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        while (que.size() != 0) {
            int size = que.size();
            System.out.print(que.getFirst().data + " ");
            while (size-- > 0) {
                Node curr = que.removeFirst();
                if (curr.left != null)
                    que.addLast(curr.left);
                if (curr.right != null)
                    que.addLast(curr.right);
            }
        }
    }

    public static void rightView(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                Node curr = que.removeFirst();
                if (size == 0)
                    System.out.print(curr.data + " ");
                if (curr.left != null)
                    que.addLast(curr.left);
                if (curr.right != null)
                    que.addLast(curr.right);

            }
        }
    }

    static int lwidth = 0;
    static int rwidth = 0;

    public static void width(Node root, int level) {

        if (root == null)
            return;
        lwidth = Math.min(lwidth, level);
        rwidth = Math.max(rwidth, level);
        width(root.left, level - 1);
        width(root.right, level + 1);
    }

    public static class helperVO {
        Node node;
        int vl = 0;

        helperVO(Node n, int v) {
            this.node = n;
            this.vl = v;
        }
    }

    public static void verticalOrder(Node root) {
        width(root, 0);
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        int n = rwidth - lwidth + 1;
        for (int i = 0; i < n; i++) {
            ans.add(new ArrayList<>());
        }
        LinkedList<helperVO> que = new LinkedList<>();
        que.addLast(new helperVO(root, -lwidth));
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                helperVO curr = que.removeFirst();
                ans.get(curr.vl).add(curr.node.data);
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.left, curr.vl - 1));
                if (curr.node.right != null)
                    que.addLast(new helperVO(curr.node.right, curr.vl + 1));

            }
        }
        int i = 0;
        for (ArrayList<Integer> ARR : ans) {
            System.out.print("Level:" + i++ + " -> ");
            System.out.println(ARR);
        }

    }

    public static void verticalOrderSum(Node root) {
        width(root, 0);
        int[] ans = new int[rwidth - lwidth + 1];
        LinkedList<helperVO> que = new LinkedList<>();
        que.addLast(new helperVO(root, -lwidth));
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                helperVO curr = que.removeFirst();
                ans[curr.vl] += curr.node.data;
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.left, curr.vl - 1));
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.right, curr.vl + 1));
            }
        }
        int i = 0;
        for (int ar : ans) {
            System.out.print("Level:" + i++ + " -> ");
            System.out.println(ar);
        }
    }

    public static void bottomView(Node root) {
        width(root, 0);
        int[] ans = new int[rwidth - lwidth + 1];
        LinkedList<helperVO> que = new LinkedList<>();
        que.addLast(new helperVO(root, -lwidth));
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                helperVO curr = que.removeFirst();
                ans[curr.vl] = curr.node.data;
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.left, curr.vl - 1));
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.right, curr.vl + 1));
            }
        }
        for (int ele : ans) {
            System.out.print(ele + " ");
        }
    }

    public static void topView(Node root) {
        width(root, 0);
        int[] ans = new int[rwidth - lwidth + 1];
        Arrays.fill(ans, (int) -1e8);
        LinkedList<helperVO> que = new LinkedList<>();
        que.addLast(new helperVO(root, -lwidth));
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                helperVO curr = que.removeFirst();
                if (ans[curr.vl] == (int) -1e8)
                    ans[curr.vl] = curr.node.data;
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.left, curr.vl - 1));
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.right, curr.vl + 1));
            }
        }
        for (int ele : ans) {
            System.out.print(ele + " ");
        }
    }

    static int dwidth = 0;

    public static void Dwidth(Node root, int level) {
        if (root == null)
            return;
        dwidth = Math.max(dwidth, level);
        Dwidth(root.left, level - 1);
        Dwidth(root.right, level);
    }

    public static void diagonalOrder(Node root) {
        Dwidth(root, 0);

        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        int n = -dwidth + 1;
        for (int i = 0; i < n; i++) {
            ans.add(new ArrayList<>());
        }
        LinkedList<helperVO> que = new LinkedList<>();
        que.add(new helperVO(root, -dwidth));
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                helperVO curr = que.removeFirst();
                ans.get(curr.vl).add(curr.node.data);
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.left, curr.vl - 1));
                if (curr.node.left != null)
                    que.addLast(new helperVO(curr.node.right, curr.vl + 0));
            }
        }
    }

    public static class allSol {
        int size = 0;
        int height = 0;
        boolean find = false;
        Node prev = null;
        Node pred = null;
        Node succ = null;
    }

    public static void solutionAll(Node root, int data, int level, allSol pair) {
        if (root == null)
            return;
        pair.size++;
        pair.height = Math.max(level, pair.height);
        if (root.data == data)
            pair.find = true;
        if (root.data == data && pair.pred == null)
            pair.pred = pair.prev;
        if (pair.prev != null && pair.prev.data == data && succ == null)
            pair.succ = root;

        pair.prev = root;
        solutionAll(root.left, data, level + 1, pair);
        solutionAll(root.right, data, level + 1, pair);
    }

    public static Node rightMost(Node node, Node curr) {

        while (node.right != null && node.right != curr) {
            node = curr.right;
        }
        return node;
    }

    public static void morrisIn(Node root) {
        Node curr = root;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node rightMst = rightMost(curr.left, curr);
                if (rightMst.right == null) {
                    rightMst.right = curr;
                    curr = curr.left;
                } else {
                    rightMst.right = null;
                    System.out.print(curr.data + " ");
                    curr = curr.right;
                }
            }

        }
        System.out.println();
    }

    public static void morrisPre(Node root) {
        Node curr = root;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node rightmst = rightMost(curr.left, curr);
                if (rightmst.right == null) {
                    rightmst.right = curr;
                    System.out.print(curr.data + " ");
                    curr = curr.left;
                } else {
                    rightmst.right = null;
                    curr = curr.right;
                }
            }
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = { 1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7 };
        Node root = construct(arr);
        // display(root);
        // levelOrder03(root);
        // rightView(root);
        // verticalOrder(root);
        // kFar03(root, 5, 1);
        // verticalOrderSum(root);
        topView(root);
    }
}