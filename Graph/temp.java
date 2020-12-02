import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef {
	static int reduce = 1000000007;
	static long[] factorial = new long[500005];
	static HashMap<Long, Long> map=new HashMap<>();

	public static void solve(long[] a, long[] quest, long[] remainder, long n) {
		for (Map.Entry<Long, Long> x : map.entrySet()) {
			long sum = 1;
			for (int j = 1; j <= x.getValue(); j++) {
				sum +=  combinations(x.getValue(), (long)j);
				sum%=reduce;
				quest[j] *= sum;
				quest[j]%=reduce;
			}
			remainder[(int) (x.getValue() + 1)] *= sum;
			remainder[(int) (x.getValue() + 1)]%=reduce;

		}
		long multiply = 1;
		for (int i = 1; i <= n; i++) {
			multiply *= remainder[i];
			multiply %= reduce;

			quest[i] *= multiply;
			quest[i]%=reduce;
		}
		for (int i = 1; i <= n; i++) {
			long sum = 1;
			long ans = 0;
			long res = 0;

			for (int j = 1; map.containsKey((long) i) && j <= map.get((long) i); j++) {
				long tmap = 0;
				ans = combinations(map.get((long) i),(long) j);
				tmap = ans;
				sum +=  ans ;
				sum%=reduce;
				quest[j] = (quest[j]*Inverse(sum))%reduce;
				// quest[j]%=reduce;
				ans *=quest[j];
				ans%=reduce;
				quest[j] = (quest[j] * (sum - tmap + reduce) % reduce) % reduce;
				res +=ans;
				res%=reduce;
			}
			System.out.print(res % reduce + " ");
		}

	}

	public static void main(String[] args) throws java.lang.Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
		int t = Integer.parseInt(br.readLine());
		factorial[0] = 1;
		factorial[1] = 1;

		for (int i = 2; i < 500005; i++) {
			long q = (((long)(1))* i * factorial[i - 1])%reduce;
			factorial[i] = q ;
		}
		while (t-- > 0) {
			long n = Long.parseLong(br.readLine());
			long[] arr = new long[(int) (n + 1)];
			String input[] = br.readLine().split("\\s");
			map.clear();
			for (int i = 0; i < n; i++) {
			    
				arr[i] = Long.parseLong(input[i]);
				map.put(arr[i],(long) (map.getOrDefault(arr[i], (long) 0) + 1));
			}
			long quest[] = new long[(int)(n + 3)];
			long remainder[] = new long[(int)(n + 1)];
			Arrays.fill(quest, 1);
			Arrays.fill(remainder, 1);
			solve(arr, quest, remainder, n);
			System.out.println();
		}
	}
	static long m=(long)reduce;
	public static long combinations(long n, long r) {
		if (r == 0)
			return 1;
		return (((factorial[(int)n]*Inverse(factorial[(int)(n-r)]))%m)*Inverse(factorial[(int)r]))%m;
	}

	public static long Inverse(long n) {
		// long m=reduce;
		return recursive(n,m - 2);
	}

	public static long recursive(long n, long p) {
		// long m=reduce;
		long a = 1;
		while (p != 0) {
			if ((p&1) > 0)a = (a  * n) % m;
			n = (n * n) % m;
			p >>= 1;
		}
		return a % m;
	}
}
