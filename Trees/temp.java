import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        long[][] dp = new long[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = scn.nextInt();
            }
        }
        int k = n - 1;
        if (k == 0) {
            System.out.println(dp[0][0]);
            return;
        }
        boolean flag = true;
        for (int gap = -k; gap <= k; gap++) {

            if (gap <= 0) {

                if (flag) {
                    for (int j = 0, i = j - gap; j <= k && i <= k; j++, i++) {
                        System.out.println(dp[i][j]);
                        // System.out.println(i+","+j+" ");
                    }
                    flag = !flag;
                } else {
                    for (int i = k, j = i + gap; i >= 0 && j >= 0; i--, j--) {
                        System.out.println(dp[i][j]);
                        // System.out.println(i+","+j+" ");
                    }
                    flag = !flag;
                }
            } else {
                if (flag) {
                    for (int i = 0, j = i + gap; i <= k && j <= k; i++, j++) {
                        System.out.println(dp[i][j]);
                        // System.out.println(i+","+j+" ");
                    }
                    flag = !flag;
                } else {

                    for (int j = k, i = j - gap; i >= 0 && j >= 0; i--, j--) {
                        System.out.println(dp[i][j]);
                        // System.out.println(i+","+j+" ");
                    }
                    flag = !flag;
                }

            }

        }
    }
}