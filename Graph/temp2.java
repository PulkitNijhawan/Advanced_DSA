/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef {
    static HashMap<Long, Long> mp = new HashMap<>();

    public static long solve(long n, long k, ArrayList<Long> a) {
        long answer = (long) 1e18;
        long calls[][] = new long[(int) (n + 1)][(int) (n + 1)];
        for (int i = 0; i < n; i++) {
            mp.clear();
            for (long j = i; j < n; j++) {
                if (j == 0) {
                    calls[i][(int) j] = 0;
                } else {
                    calls[i][(int) j] = calls[i][(int) (j - 1)];
                }
                if (mp.containsKey(a.get((int) j))) {
                    if (mp.get(a.get((int) j)) == 1) {
                        calls[i][(int) j]++;
                    }
                    calls[i][(int) j]++;
                }
                mp.put(a.get((int) j), mp.getOrDefault(a.get((int) j), (long) 0) + 1);

            }

        }
        long dp[][] = new long[101][1001];
        for (int i = 2; i <= table; i++) {
            long d=0;
            dp[i][1] = d;
        }
        for (int i = 1; i < n + 1; i++){
            long pul=calls[0][i - 1];
            dp[1][i] = pul;
        }

        long table = 100;

        for (int i = 2; i <= table; i++) {
            for (int j = 2; j <= n; j++) {
                long res = (long) 1e18;
                for (int p = 1; p < j; p++) {
                    res = Math.min(res, dp[i - 1][p] + calls[p][j - 1]);
                }
                dp[i][j] = res;
            }
        }
        for (table = 1; table <= 100; table++) {
            answer = Math.min(table * k + dp[(int) table][(int) n], answer);
        }
        return answer;

    }

    public static void main(String[] args) throws java.lang.Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            String input[] = br.readLine().split("\\s");
            long n = Long.parseLong(input[0]);
            long k = Long.parseLong(input[1]);
            ArrayList<Long> a = new ArrayList<>();
            String input1[] = br.readLine().split("\\s");
            for (int i = 0; i < n; i++) {
                long y = Long.parseLong(input1[i]);
                a.add((long) y);
            }

            

            System.out.println(solve(n,k,a));
        }
    }
}
