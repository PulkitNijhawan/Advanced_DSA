
import java.util.*;

public class temp {
    static int min=10;
    public static boolean isBal(String query){
        // if(query.charAt(0)==')'||query.charAt(query.length()-1)=='(')return false;
        Stack<Character> st = new Stack<Character>();
        for(int i=0;i<query.length();i++){
            if(query.charAt(i)=='(')st.push('(');
            else if(query.charAt(i)==')'){
                if(st.isEmpty())return false;
                st.pop();
            }
        }
        if(!st.isEmpty())return false;
        else return true;
    }
   
    
    
    public static void solve(String ques,int rem,ArrayList<String> ans){
        if(ques.length()==0)return;
        if(rem>min)return;
        if(isBal(ques)){
            if(rem<=min){
                ans.add(ques);
                min=rem;
                return;
            }
            
        }
            
            
            for(int i=0;i<ques.length();i++){
                if(ques.charAt(i)=='('||ques.charAt(i)==')'){
                    String roq=ques.substring(0,i)+ques.substring(i+1);
                    solve(roq,rem+1);
                }
            }
        
    }
    public static void main(String[] args) {
        Scanner scn=new Scanner(System.in);
        String ques=scn.nextLine();
        solve(ques,0);
        System.out.println(ans.get(8)=="(v)()()");
        // System.out.println();
        // ArrayList<String> res=new ArrayList<>();
        // String temp="";
        // for(int i=0;i<ans.size();i++){
        //     String ele=ans.get(i);
        //     System.out.println(ele=="(v)()()");
            
            // if(ele.length()==(ques.length()-min)&&temp!=ele)System.out.println(ele) ;
        //     temp=ele;
        // }
        // System.out.println("(v)()()"=="(v)()()");
    }
}