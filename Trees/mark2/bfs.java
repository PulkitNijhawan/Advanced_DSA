import java.util.*;

public class bfs {
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

    public static void levelOrder(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.add(root);
        while (!que.isEmpty()) {
            Node rNode = que.removeFirst();
            System.out.print(rNode.data + " ");
            if (rNode.right != null)
                que.add(rNode.right);
            if (rNode.left != null)
                que.add(rNode.left);
        }
    }

    public static void bfs01(Node root) {
        LinkedList<Node> que1 = new LinkedList<>();
        LinkedList<Node> que2 = new LinkedList<>();
        que1.addLast(root);
        int level = 0;
        System.out.print("Level: " + level + "-> ");
        while (!que1.isEmpty()) {
            Node rNode = que1.removeFirst();
            System.out.print(rNode.data + " ");
            if (rNode.right != null)
                que2.addLast(rNode.right);
            if (rNode.left != null)
                que2.addLast(rNode.left);
            if (que1.isEmpty()) {
                level++;
                LinkedList<Node> temp = que1;
                que1 = que2;
                que2 = temp;
                System.out.print("\nLevel: " + level + "-> ");
            }

        }
    }

    public static void bfs02(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        que.addLast(null);
        int level = 0;
        System.out.print("Level: " + level + "-> ");
        while (true) {
            Node rNode = que.removeFirst();
            if (que.isEmpty())
                break;
            if (rNode == null) {
                que.addLast(null);
                level++;
                System.out.print("\nLevel: " + level + "-> ");
                continue;
            }
            System.out.print(rNode.data + " ");
            if (rNode.right != null)
                que.addLast(rNode.right);
            if (rNode.left != null)
                que.addLast(rNode.left);

        }
    }

    public static void bfs03(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        int level = 0;
        System.out.print("Level: " + level + "-> ");
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                Node rNode = que.removeFirst();
                System.out.print(rNode.data + " ");
                if (rNode.right != null)
                    que.addLast(rNode.right);
                if (rNode.left != null)
                    que.addLast(rNode.left);

            }
            level++;
            System.out.print("\nLevel: " + level + "-> ");
        }
    }

    public static void leftView(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        while (!que.isEmpty()) {
            int size = que.size();
            System.out.print(que.getFirst().data + " ");
            while (size-- > 0) {
                Node rNode = que.removeFirst();
                if (rNode.left != null)
                    que.addLast(rNode.left);
                if (rNode.right != null)
                    que.addLast(rNode.right);

            }
        }
    }

    public static void rightView(Node root) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(root);
        while (!que.isEmpty()) {
            int size = que.size();
            Node prev = null;
            while (size-- > 0) {
                Node rNode = que.removeFirst();
                if (rNode.left != null)
                    que.addLast(rNode.left);
                if (rNode.right != null)
                    que.addLast(rNode.right);
                prev = rNode;
            }
            System.out.print(prev.data + " ");
        }
    }

    static int leftMinValue = (int) 1e8;
    static int rightMaxValue = (int) -1e8;

    public static void width(Node root, int level) {
        if (root == null)
            return;
        leftMinValue = Math.min(leftMinValue, level);
        rightMaxValue = Math.max(rightMaxValue, level);
        width(root.left, level - 1);
        width(root.right, level + 1);
    }

    public static class pairVO {
        Node node = null;
        int level;

        pairVO(Node n, int l) {
            this.node = n;
            this.level = l;
        }
    }

    public static void verticalOrder(Node root) {
        width(root, 0);
        ArrayList<Integer>[] ans = new ArrayList[rightMaxValue - leftMinValue + 1];
        for (int p = 0; p < ans.length; p++)
            ans[p] = new ArrayList<>();
        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(root, -leftMinValue));
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rVO = que.removeFirst();
                ans[rVO.level].add(rVO.node.data);
                if (rVO.node.left != null)
                    que.addLast(new pairVO(rVO.node.left, rVO.level - 1));
                if (rVO.node.right != null)
                    que.addLast(new pairVO(rVO.node.right, rVO.level + 1));

            }

        }
        int i = 0;
        for (ArrayList<Integer> x : ans) {
            System.out.print("Level: " + i++ + "-> ");
            System.out.println(x);
        }
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 40, -1, -1, 50, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1 };
        Node root = constructTree(arr);
        // levelOrder(root);
        // bfs03(root);
        // rightView(root);
        verticalOrder(root);
    }
}
