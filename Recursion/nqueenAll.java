import java.util.*;

public class nqueenAll {
    public static int queen1D(int n, int qpsf, int idx, String ans) {
        if (qpsf == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i <= n; i++) {
            cnt += queen1D(n, qpsf - 1, i + 1, ans + "b" + i + " ");
        }
        return cnt;
    }

    public static int queen1D02(int n, int qpsf, int idx, String ans) {
        if (idx == n + 1 || qpsf == 0) {
            if (qpsf == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (qpsf >= 0)
            cnt += queen1D02(n, qpsf - 1, idx + 1, ans + "b" + idx + " ");
        cnt += queen1D02(n, qpsf, idx + 1, ans);
        return cnt;
    }

    public static int queen2D(int n, int qpsf, int idx, String ans) {
        if (qpsf == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        int r = idx / n;
        int c = idx % n;
        for (int i = idx; i < n * n; i++) {
            cnt += queen2D(n, qpsf - 1, i + 1, ans + "(" + r + "," + c + ") ");
        }
        return cnt;
    }

    public static int queenPermu1D(int[] arr, int qpsf, String ans) {
        if (qpsf == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = 1; i <= arr.length; i++) {

            if (arr[i - 1] != 1) {
                arr[i - 1] = 1;
                cnt += queenPermu1D(arr, qpsf - 1, ans + "b" + i + " ");
                arr[i - 1] = 0;
            }

        }
        return cnt;
    }

    public static int queenPermu1D02(int[] arr, int qpsf, int idx, String ans) {
        if (idx == arr.length + 1 || qpsf == 0) {
            if (qpsf == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (idx <= arr.length && arr[idx - 1] != 1) {
            arr[idx - 1] = 1;
            cnt += queenPermu1D02(arr, qpsf - 1, 1, ans + "b" + idx + " ");
            arr[idx - 1] = 0;
        }
        cnt += queenPermu1D02(arr, qpsf, idx + 1, ans);
        return cnt;
    }
    
    public static void main(String[] args) {
        int[] arr = new int[4];
        System.out.println(queenPermu1D02(arr, 2, 1, ""));

    }
}