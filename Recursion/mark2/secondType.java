import java.util.*;

public class secondType {
    public static int nokiaKeypadVT(String ques,String[] words,String ans){
        
        if(ques.length()==0){
            System.out.println(ans);
            return 1;
        }
        int num=ques.charAt(0)-'0';
        int secondNum=-1;
        if(ques.length()>1)secondNum=(ques.charAt(0)-'0')*10 + ques.charAt(1)-'0';
        int cnt=0;
        for(int i=0;i<words[num].length();i++){
            cnt+=nokiaKeypadVT(ques.substring(1), words, ans+words[num].charAt(i));
            if(secondNum==10||secondNum==11)cnt+=nokiaKeypadVT(ques.substring(2), words, ans+words[secondNum].charAt(i));
        }
        return cnt;
    }
    public static ArrayList<String> nokiaKeypadRT(String ques,String[] words){
        if(ques.length()==1){
            ArrayList<String> baseRes=new ArrayList<>();
            String str=words[ques.charAt(0)-'0'];
            for(int i=0;i<str.length();i++){
                baseRes.add(str.charAt(i)+"");
            }
            return baseRes;
        }
        int num=ques.charAt(0)-'0';
        ArrayList<String> myAns=new ArrayList<>();
        ArrayList<String> recAns=nokiaKeypadRT(ques.substring(1), words);
        for(String s:recAns){
            for(int i=0;i<words[num].length();i++){
                myAns.add(words[num].charAt(i)+s);
            }
        }
        return myAns;
    }
    public static int encodings(String ques,String ans){
        if(ques.length()==0){
            System.out.println(ans);
            return 1;
        }
        char ch=(char)(ques.charAt(0)+48);
        char secondCh='1';
        if(ques.length()>1)secondCh=(char)(((ques.charAt(0)-'0')*10 + ques.charAt(1)-'0')+'a'-1);
        int cnt=0;
        cnt+=encodings(ques.substring(1), ans+ch);
        if(ques.length()>1&&secondCh<='z')cnt+=encodings(ques.substring(2), ans+secondCh);
        return cnt;
    }
    static int[][] dirA={{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
    static String[] dirN={"E","H","N","V","W","D","S","A"};
    public static int floodFill(int r,int c,boolean[][] board,String ans){
        if(r==board.length-1&&c==board[0].length-1){
            System.out.println(ans);
            return 1;
        }
        board[r][c]=true;
        int cnt=0;
        for(int d=0;d<dirA.length;d++){
            int x=r+dirA[d][0];
            int y=c+dirA[d][1];
            if(x>=0&&y<=0&&x<board.length&&y<board[0].length&&!board[x][y]){
                cnt+=floodFill(x, y, board, ans+dirN[d]);
            }
        }
        board[r][c]=false;
        return cnt;
    }
    public static void solve() {
        String[] words = { ":;/", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "&*%", "#@$","`!(" };
        // System.out.println(nokiaKeypadVT("010",words,""));
        System.out.println(encodings("123", ""));
    }

    public static void main(String[] args) {
        solve();
    }
}
