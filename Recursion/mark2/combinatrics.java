package mark2;

import java.util.*;

public class combinatrics {
    public static int permuteInfiRT(int[] arr, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int c : arr) {
            if (tar - c >= 0)
                cnt += permuteInfiRT(arr, tar - c, ans + c);
        }
        return cnt;
    }

    public static int combiInfiRT(int[] arr, int idx, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0)
                cnt += combiInfiRT(arr, i, tar - arr[i], ans + arr[i] + " ");
        }
        return cnt;
    }
    public static int combiFiniteRT(int[] arr,int idx,int tar,String ans){
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0)
                cnt += combiFiniteRT(arr, i+1, tar - arr[i], ans + arr[i] + " ");
        }
        return cnt;
    }
    public static int permuteFiniteRT(int[] arr,int tar,boolean[] vis,String ans){
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt=0;
        
        for(int i=0;i<arr.length;i++){
            vis[i]=true;
            if(!vis[i]&&tar-arr[i]>=0)cnt+=permuteFiniteRT(arr, tar-arr[i],vis, ans+arr[i]+" ");
            vis[i]=false;
        }
        return cnt;
    }
    public static int permuInfiVT(int[] arr,int idx,int tar,String ans){
        if(idx==arr.length||tar==0){
            if(tar==0){
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt=0;
        if(tar-arr[idx]>=0)cnt+=permuInfiVT(arr, 0, tar-arr[idx], ans+arr[idx]);
        cnt+=permuInfiVT(arr, idx+1, tar, ans);
        return cnt;
    }
    public static int combiInfiVT(int[] arr,int idx,int tar,String ans){
        if(idx==arr.length||tar==0){
            if(tar==0){
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt=0;
        if(tar-arr[idx]>=0)cnt+=combiInfiVT(arr, idx, tar-arr[idx], ans+arr[idx]);
        cnt+=combiInfiVT(arr, idx+1, tar, ans);
        return cnt;
    }
    public static int combiFiniteVT(int[] arr,int idx,int tar,String ans){
        if(idx==arr.length||tar==0){
            if(tar==0){
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt=0;
        if(tar-arr[idx]>=0)cnt+=combiFiniteVT(arr, idx+1, tar-arr[idx], ans+arr[idx]);
        cnt+=combiFiniteVT(arr, idx+1, tar, ans);
        return cnt;
    }
    public static int permuFiniteVT(int[] arr,int idx,int tar,boolean[] vis,String ans){
        if(idx==arr.length||tar==0){
            if(tar==0){
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt=0;
        if(!vis[idx]&&tar-arr[idx]>=0){
            vis[idx]=true;
            cnt+=permuFiniteVT(arr, 0, tar-arr[idx],vis, ans+arr[idx]);
            vis[idx]=false;
        }
        cnt+=permuFiniteVT(arr, idx+1, tar,vis, ans);
        return cnt;
    }
    public static void solve() {
        int[] arr = { 2, 3, 5, 7 };
        boolean[] vis=new boolean[arr.length];
        System.out.println(permuFiniteVT(arr, 0, 10,vis, ""));
    }

    public static void main(String[] args) {
        solve();
    }
}
