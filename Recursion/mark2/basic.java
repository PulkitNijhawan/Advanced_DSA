package mark2;

import java.util.*;

public class basic {
    public static int powerLog(int x, int y) {

        if (y == 1 || y == 0)
            return y == 0 ? 1 : x;
        int half = powerLog(x, y / 2);
        return y % 2 == 0 ? half * half : half * half * x;
    }

    public static boolean findArr(int[] arr, int i, int k) {
        if (i == arr.length)
            return false;
        boolean res = findArr(arr, i + 1, k);
        if (arr[i] == k)
            res = true;
        return res;
    }

    public static int maximumArr(int[] arr, int i) {
        if (i == arr.length - 1)
            return arr[i];
        return Math.max(maximumArr(arr, i + 1), arr[i]);
    }

    public static int findLast(int[] arr, int i, int k) {
        if (i == arr.length)
            return -1;
        int ans = findLast(arr, i + 1, k);
        if (arr[i] == k)
            return ans == -1 ? i : ans;
        return ans;
    }

    public static ArrayList<String> premuteRT(String str) {
        if (str.length() == 0) {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }
        char ch = str.charAt(0);
        ArrayList<String> recAns = premuteRT(str.substring(1));
        ArrayList<String> myAns = new ArrayList<>();
        for (String s : recAns) {
            if (s == "") {
                myAns.add(s + ch);
                continue;
            }
            for (int i = 0; i <= s.length(); i++) {
                myAns.add(s.substring(0, i) + ch + s.substring(i));
            }
        }
        return myAns;
    }

    public static int permuteVT(String ques, String ans) {
        if (ques.length() == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = 0; i < ques.length(); i++) {
            cnt += permuteVT(ques.substring(0, i) + ques.substring(i + 1), ans + ques.charAt(i));
        }
        return cnt;
    }

    public static int permuteDupliVT(String ques, String ans) {
        if (ques.length() == 0) {
            System.out.println(ans);
            return 1;
        }
        int repeat[] = new int[26];
        int cnt = 0;
        for (int i = 0; i < ques.length(); i++) {
            if (repeat[ques.charAt(i) - 'a'] != 1)
                cnt += permuteDupliVT(ques.substring(0, i) + ques.substring(i + 1), ans + ques.charAt(i));
            repeat[ques.charAt(i) - 'a'] = 1;

        }
        return cnt;
    }

    public static void solve() {
        // System.out.println(powerLog(2,5));
        int[] arr = { 5, 2, 5, 5, 5 };
        // System.out.println(findLast(arr,0,4));
        System.out.println(permuteDupliVT("abcac", ""));
        // System.out.print(permAns);
    }

    public static void main(String[] args) {

        solve();
    }
}
