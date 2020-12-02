import java.util.*;

public class wordBreak {
    public static String[] words = { "mobile", "samsung", "sam", "sung", "man", "mango", "icecream", "and", "go" , "like", "i", "ice", "cream", "ilik", "esa" };
    public static boolean contain(String word){
        for(String str:words){
            if(str.equals(word))return true;
        }
        return false;
    }
    public static int wordbreak(int idx,String ques,String ans){
        if(idx==ques.length()){
            System.out.println(ans);
            return 1;
        }
        int cnt=0;
        for(int i=idx+1;i<=ques.length();i++){
            String w=ques.substring(idx, i);
            if(contain(w))cnt+=wordbreak(i, ques, ans+w+" ");
        }
        return cnt;
    }
    public static void main(String[] args) {
        System.out.println(wordbreak(0, "ilikesamsungandmango", ""));
    }
}