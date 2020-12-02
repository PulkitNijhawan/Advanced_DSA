import java.util.Scanner;

public class Main {

	public static int solve(int a,int b){
        int ans=1;
        for(int i=1;i<=a;i++){
            ans*=i;
        }
        return ans%b;
    }
	public static void main(String[] args) {
		Scanner scn=new Scanner(System.in);
        int t=scn.nextInt();
        while(t-->0){
            int a=scn.nextInt();
            int b=scn.nextInt();
            System.out.println(solve(a,b));
        }

	}

}
