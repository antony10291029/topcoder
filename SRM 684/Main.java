import java.io.BufferedInputStream;
import java.util.Scanner;

/**
 * @author resry.lqy
 * @version $Id: Test.java, v 0.1 16/5/15 ÉÏÎç9:49 resry.lqy Exp $$
 */
public class Main {
    private static final int mod = 9973;

    /**
     * cal a^b
     *
     * @param a
     * @param b
     * @return
     */
    private int pow(int a, int b) {
        int t = 1;
        int res = 1;
        while (b > 0) {
            if (b%2 != 0) {
                res = res * t % mod;
            }
            t = t * a % mod;
            b >>= 1;
        }
        return res;
    }
    private void main() {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        while (sc.hasNext()) {
            int n = sc.nextInt();
            String s = sc.nextLine();
            int[] t = new int[s.length()+1];
            t[0] = 1;
            for (int i = 0; i < s.length(); ++i) {
                t[i+1] = t[i] * (s.charAt(i)-28) % mod;
            }
            for (int i = 0; i < n; ++i) {
                int l = sc.nextInt();
                int r = sc.nextInt();
                System.out.println(t[r] * pow(t[l-1], mod-2) % mod);
            }
        }
    }
    public static void main(String[] args) {
        new Main().main();
    }
}