 
import java.util.*;
public class temp { 
    static int largestPower(int n, int p) { 
        int x = 0; 
        while (n > 0) { 
            n /= p; 
            x += n; 
        } 
        return x; 
    } 
    static int power(int x, int y, int p) { 
        int res = 1; // Initialize result 
        x = x % p; // Update x if it is more than or 
    
        while (y > 0) { 
            // If y is odd, multiply x with result 
            if (y % 2 == 1) { 
                res = ((res%p) * (x%p)) % p; 
            } 
  
            // y must be even now 
            y = y >> 1; // y = y/2 
            x = ((x%p) * (x%p)) % p; 
        } 
        return res; 
    } 
  
    static int modFact(int n, int p) { 
        if (n >= p) { 
            return 0; 
        } 
  
        int res = 1; 
        boolean isPrime[] = new boolean[n + 1]; 
        Arrays.fill(isPrime, true); 
        for (int i = 2; i * i <= n; i++) { 
            if (isPrime[i]) { 
                for (int j = 2 * i; j <= n; j += i) { 
                    isPrime[j] = false; 
                } 
            } 
        } 
  
        
        for (int i = 2; i <= n; i++) { 
            if (isPrime[i]) { 
                int k = largestPower(n, i)%p; 
                res = ((res%p) * (power(i, k, p)%p)) % p; 
            } 
        } 
        return res; 
    } 
  
// Driver method 
    static public void main(String[] args) { 
        Scanner scn=new Scanner(System.in);
        int t=scn.nextInt();
        while(t-->0){
            int n=scn.nextInt();
            int p=scn.nextInt();
        	System.out.println(modFact(n,p));
        }
  
    } 
} 