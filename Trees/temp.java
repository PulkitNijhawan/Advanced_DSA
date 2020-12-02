class Solution {
    public int sumEvenGrandparent(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int ans = 0;
        if (root.val % 2 == 0) {
            ans = getsum(root);
        }
        int a = sumEvenGrandparent(root.left);
        int b = sumEvenGrandparent(root.right);
        return ans + a + b;
    }

    public int getsum(TreeNode root) {
        int ans = 0;
        if (root.left != null) {
            if (root.left.left != null)
                ans += root.left.left.val;
            if (root.left.right != null)
                ans += root.left.right.val;
        }
        if (root.right != null) {
            if (root.right.left != null)
                ans += root.right.left.val;
            if (root.right.right != null)
                ans += root.right.right.val;
        }
        return ans;
    }
}