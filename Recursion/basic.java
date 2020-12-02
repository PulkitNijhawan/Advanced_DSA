import java.util.*;

public class basic {
    public static Scanner scn = new Scanner(System.in);

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {
        // zero();
        // arrays();
        strings();
        
    }

    public static void zero() {
        int a;
        int b;
        a = scn.nextInt();
        b = scn.nextInt();
        power_log(a, b);
    }

    public static int power_log(int a, int b) {
        if (b == 0)
            return 1;
        int halfAns = power_log(a, b / 2);
        halfAns *= halfAns;
        return halfAns * (b % 2 != 0 ? b : 1);
    }

    public static void arrays() {
        int[] arr = { 1, 2, 3, 4 };
        System.out.println(lastIdx(arr, 0, 2));
        int[] ans = allIdx(arr, 0, 2, 0);
    }

    public static int lastIdx(int[] arr, int idx, int k) {
        if (idx == arr.length)
            return -1;

        int backAns = lastIdx(arr, idx + 1, k);
        if (backAns != -1)
            return backAns;
        return arr[idx] == k ? idx : -1;
    }

    public static int[] allIdx(int[] arr, int idx, int k, int cnt) {
        if (idx == arr.length) {
            return new int[cnt];
        }
        if (arr[idx] == k)
            cnt++;
        int[] recAns = allIdx(arr, idx + 1, k, cnt + 1);
        if (arr[idx] == k) {
            recAns[cnt - 1] = idx;
        }
        return recAns;
    }

    public static void strings() {
        // System.out.println(subseq_("abc"));
        // System.out.print(permutation02("abc"));
        System.out.print(permutationUnique("aba",""));
    }

    public static ArrayList<String> subseq_(String ques) {
        if (ques.length() == 0) {
            ArrayList<String> baseRes = new ArrayList<>();
            baseRes.add("");
            return baseRes;
        }
        char ch = ques.charAt(0);
        ArrayList<String> recAns = subseq_(ques.substring(1));
        ArrayList<String> myAns = new ArrayList<>();
        for (String str : recAns) {
            myAns.add(str);
            myAns.add(str + ch);
        }

        return myAns;
    }

    public static int permutation(String ques, String ans) {
        if (ques.length() == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = 0; i < ques.length(); i++) {
            String roq = ques.substring(0, i) + ques.substring(i + 1);
            cnt += permutation(roq, ans + ques.charAt(i));
        }
        return cnt;
    }

    public static ArrayList<String> permutation02(String ques) {
        if (ques.length() == 1) {
            ArrayList<String> baseRes = new ArrayList<>();
            baseRes.add(ques);
            return baseRes;
        }

        char ch = ques.charAt(0);
        ArrayList<String> recAns = permutation02(ques.substring(1));
        ArrayList<String> myAns = new ArrayList<>();
        for (String str : recAns) {
            for (int i = 0; i <= str.length(); i++) {
                String ans = str.substring(0, i) + ch + str.substring(i);
                myAns.add(ans);
            }
        }
        return myAns;
    }
    public static int permutationUnique(String ques,String ans){
        if(ques.length()==0){
            System.out.println(ans);
            return 1;
        }
        int cnt=0;
        boolean[] vis=new boolean[26];
        for(int i=0;i<ques.length();i++){
            char ch=ques.charAt(i);
            if(!vis[ch-'a']){
                vis[ch-'a']=true;
                cnt+=permutationUnique(ques.substring(0, i)+ques.substring(i+1), ans+ch);
            }
        }
        return cnt;
    }
}