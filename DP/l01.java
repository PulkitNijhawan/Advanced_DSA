import java.util.*;

public class l01 {
    static int[][] dirA = { { -1, 1 }, { 0, 1 }, { 1, 1 } };

    public static int goldMemo(int sr, int sc, int[][] arr, int[][] dp) {
        if (sc == arr[0].length - 1) {
            return dp[sr][sc] = arr[sr][sc];
        }
        if (dp[sr][sc] != 0)
            return dp[sr][sc];
        int maxdir = 0;
        for (int i = 0; i < dirA.length; i++) {
            int x = sr + dirA[i][0];
            int y = sc + dirA[i][1];
            if (x >= 0 && y >= 0 && x < arr.length && y < arr[0].length) {
                maxdir = Math.max(maxdir, goldMemo(x, y, arr, dp));
            }
        }
        return dp[sr][sc] = maxdir + arr[sr][sc];
    }

    public static int goldDP(int[][] arr, int[][] dp) {
        for (int sc = arr[0].length - 1; sc >= 0; sc--) {
            for (int sr = arr.length - 1; sr >= 0; sr--) {
                if (sc == arr[0].length - 1) {
                    dp[sr][sc] = arr[sr][sc];
                    continue;
                }
                int maxdir = 0;
                for (int i = 0; i < dirA.length - 1; i++) {
                    int x = sr + dirA[i][0];
                    int y = sc + dirA[i][1];
                    if (x >= 0 && y >= 0 && x < arr.length && y < arr[0].length) {
                        maxdir = Math.max(maxdir, dp[x][y]);
                    }
                }
                dp[sr][sc] = maxdir + arr[sr][sc];
            }
        }
        int ans = 0;
        for (int i = 0; i < arr.length; i++) {
            ans = Math.max(ans, dp[i][0]);
        }
        return ans;
    }

    public static void main(String[] args) {
        int[][] arr = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
        int[][] dp = new int[arr.length][arr[0].length];
        // int ans=0;
        // for(int i=0;i<arr.length;i++){
        // ans=Math.max(ans,goldMemo(i,0,arr,dp));
        // }
        System.out.print(goldDP(arr, dp));
    }
}