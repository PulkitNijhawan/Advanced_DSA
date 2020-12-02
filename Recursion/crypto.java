import java.util.*;
public class crypto {
    static String str1="send";
    static String str2="more";
    static String str3="money";
    static int boolArr=0;
    public static int utility(String str,int[] hashmap){
        int ans=0;
        for(int i=0;i<str.length();i++){
            ans=ans*10+(hashmap[str.charAt(i)-'a']);
        }
        return ans;
    }
    public static int solve(String s,int[] hashmap,int idx){
        if(idx==s.length()){
            int one=utility(str1,hashmap);
            int two=utility(str2,hashmap);
            int thr=utility(str3,hashmap);
            if(one+two==thr){
                for(int x=0;x<hashmap.length;x++){
                    if(hashmap[x]>0){
                        System.out.print((char)(x+'a')+":"+hashmap[x]+" ");
                    }
                }
                System.out.println();
                return 1;
            }
            return 0;
        }
        int cnt=0;
        for(int i=0;i<=9;i++){
            int mask=1<<i;
            if((boolArr&mask)==0){
                boolArr^=mask;
                hashmap[s.charAt(idx)-'a']=i;
                cnt+=solve(s, hashmap, idx+1);
                boolArr^=mask;
            }
        }
        return cnt;
    }
    public static void main(String[] args){
        String s=str1+str2+str3;
        int[] compress=new int[26];
        for(int i=0;i<s.length();i++){
            compress[s.charAt(i)-'a']++;
        }
        s="";
        for(int i=0;i<compress.length;i++){
            if(compress[i]>0)s+=(char)(i+'a');
        }
        int[] hashmap=new int[26];
        System.out.println(solve(s,hashmap,0));
        // System.out.println(s);
    }
}