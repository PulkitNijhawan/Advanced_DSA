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
            return -1;
        return max(height(root.left), height(root.right)) + 1;
    }

    static ArrayList<Node> n2rp = new ArrayList<>();

    public static boolean n2rp(Node root, int k) {
        if (root == null || root.data == k) {
            if (root != null && root.data == k) {
                n2rp.add(root);
                return true;
            }
            return false;
        }
        boolean res = n2rp(root.left, k) || n2rp(root.right, k);
        if (res)
            n2rp.add(root);
        return res;
    }

    public static ArrayList<Node> n2rp02(Node root, int k) {
        if (root == null || root.data == k) {
            if (root != null && root.data == k) {
                ArrayList<Node> baseRes = new ArrayList<>();
                baseRes.add(root);
                return baseRes;
            }
            return new ArrayList<>();
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

    public static Node lca(ArrayList<Node> one, ArrayList<Node> two) {
        if (one.size() == 1 || two.size() == 1)
            return one.get(one.size() - 1);
        int i = one.size() - 1;
        int j = two.size() - 1;
        while (i != 0 && j != 0) {
            if (one.get(i).data != two.get(j).data) {
                break;
            }
            i--;
            j--;
        }
        return one.get(i + 1);
    }

    static Node lcaNode = null;

    public static boolean lca02(Node root, int a, int b) {
        if (root == null)
            return false;
        boolean selfAns = false;
        if (root.data == a || root.data == b) {
            selfAns = true;
        }
        boolean rightAns = lca02(root.right, a, b);
        if (lcaNode != null)
            return true;
        boolean leftAns = lca02(root.left, a, b);
        if (lcaNode != null)
            return true;
        if ((selfAns && rightAns) || (selfAns && leftAns) || (leftAns && rightAns))
            lcaNode = root;
        return leftAns || rightAns || selfAns;
    }

    public static void kDown(Node rt, int level, Node blockNode, ArrayList<Node> ans) {
        if (rt == null || rt == blockNode)
            return;
        if (level == 0) {
            ans.add(rt);
            return;
        }
        kDown(rt.left, level - 1, blockNode, ans);
        kDown(rt.right, level - 1, blockNode, ans);
    }

    public static void kfar01(Node root, int d, int k) {
        ArrayList<Node> n2rp = n2rp02(root, d);
        ArrayList<Node> ans = new ArrayList<>();
        Node blockNode = null;
        for (int i = 0; i < n2rp.size(); i++) {
            kDown(n2rp.get(i), k - i, blockNode, ans);
        }
        System.out.println(ans);
    }

    public static int kfar02(Node root, int d, int k, ArrayList<Node> ans) {
        if (root == null)
            return -1;
        if (root.data == d) {
            kDown(root, k, null, ans);
            return 1;
        }
        int leftAns = kfar02(root.left, d, k, ans);
        if (leftAns > 0) {
            if (k - leftAns >= 0)
                kDown(root, k - leftAns, root.left, ans);
            return leftAns + 1;
        }
        int rightAns = kfar02(root.right, d, k, ans);
        if (rightAns > 0) {
            if (k - rightAns >= 0)
                kDown(root, k - rightAns, root.right, ans);
            return rightAns + 1;
        }
        return -1;
    }

    public static int diameter(Node root) {
        if (root == null)
            return 0;
        return max((height(root.left) + height(root.right) + 2), diameter(root.left), diameter(root.right));
    }

    static int diameter = -1;

    public static int diameter02(Node root) {
        if (root == null)
            return -1;
        int l = diameter02(root.left);
        int r = diameter02(root.right);
        diameter = max((l + r + 2), diameter);
        return max(l, r) + 1;
    }

    public static List<List<Integer>> pathSum2(Node root, int sum) {
        if (root == null)
            return new ArrayList<>();
        if (root.right == null && root.left == null && root.data == sum) {
            List<List<Integer>> baseRes = new ArrayList<>();
            baseRes.add(new ArrayList<Integer>());
            baseRes.get(0).add(root.data);
            return baseRes;
        }
        List<List<Integer>> myAns = new ArrayList<>();
        List<List<Integer>> leftAns = pathSum2(root.left, sum - root.data);
        if (leftAns.size() != 0) {
            for (List<Integer> x : leftAns) {
                x.add(0, root.data);
                myAns.add(x);
            }
        }
        List<List<Integer>> rightAns = pathSum2(root.right, sum - root.data);
        if (rightAns.size() != 0) {
            for (List<Integer> x : rightAns) {
                x.add(0, root.data);
                myAns.add(x);
            }
        }
        return myAns;
    }

    static int l2lMax = (int) -1e8;

    public static int leaf2leaf(Node root) {
        if (root == null)
            return (int) (-1e8 - 1);
        if (root.left == null && root.right == null)
            return root.data;
        int leftAns = leaf2leaf(root.left);
        int rightAns = leaf2leaf(root.right);
        // rightAns=rightAns==(int)(-1e8-1)?0:rightAns;
        if (root.left != null && root.right != null)
            l2lMax = max(l2lMax, leftAns + rightAns + root.data);
        return max(leftAns, rightAns) + root.data;

    }

    public static Node preInConst(int ps, int pe, int is, int ie, int[] pre, int[] in) {
        if (ps > pe)
            return null;
        Node node = new Node(pre[ps]);
        int idx = is;
        while (in[idx] != pre[ps])
            idx++;
        int len = idx - is;
        node.left = preInConst(ps + 1, pe + len, is, idx - 1, pre, in);
        node.right = preInConst(ps + len + 1, pe, idx + 1, ie, pre, in);
        return node;
    }

    static Node prevDll = null;
    static Node headDll = null;

    public static void tree2Dll(Node root) {
        if (root == null)
            return;
        tree2Dll(root.left);
        if (headDll == null)
            headDll = root;
        else {
            prevDll.right = root;
            root.left = prevDll;
        }
        prevDll = root;
        tree2Dll(root.right);
    }

    static int postIdx = 0;

    public static boolean checkTree(int ps, int pe, int is, int ie, int[] pre, int[] in, int[] post) {
        if (ps > pe)
            return true;
        int node = pre[ps];
        int idx = is;
        while (in[idx] != pre[ps])
            idx++;
        int len = idx - is;
        if (!checkTree(ps + 1, pe + len, is, idx - 1, pre, in, post))
            return false;
        if (!checkTree(ps + len + 1, pe, idx + 1, ie, pre, in, post))
            return false;
        if (post[postIdx++] != node)
            return false;
        return true;
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 40, -1, -1, 50, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1 };
        Node root = constructTree(arr);
        // display(root);
        // System.out.println(n2rp(root, 100));
        // for (Node x : n2rp) {
        // System.out.print(x.data + " ");
        // }
        // ArrayList<Node> one = n2rp02(root, 70);
        // ArrayList<Node> two = n2rp02(root, 70);
        // ArrayList<Node> ans=new ArrayList<>();
        // System.out.println(kfar02(root, 60, 3,ans));
        // System.out.println(ans);

        // diameter02(root);
        // System.out.println(diameter);
        leaf2leaf(root);
        System.out.println(l2lMax);
    }
}