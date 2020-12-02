import java.util.*;

public class bits {
    public static int offToOn(int num, int k) {
        int mask = (1 << (k - 1));
        return (num | mask);

    }

    public static int onToOff(int num, int k) {
        int mask = (~(1 << (k - 1)));
        return (num & mask);
    }

    public static int cntSetBits(int num) {
        int cnt = 0;
        for (int i = 0; i < 32; i++) {
            int mask = (1 << k);
            if ((num & mask) != 0)
                cnt++;
        }
        return cnt;
    }
    public static int cntSetBits02(int num){
        int cnt=0;
        while(num!=0){
            if((num & 1) != 0)cnt++;
            num>>>=1; // >>> for unsign reason that is msb!=1
        }
        return cnt;
    }
    public static int cntSetBits03(int num){
        int cnt=0;
        while(num!=0){
            cnt++;
            num &= (num - 1);
        }
        return cnt;
    }
    public static boolean powerOfTwo(int n){
        return n>0 && !(n&(n-1));
    }
    
    public static void main(String[] args) {
        int num = 17;

        System.out.print(onToOff(num, 2));
    }
}