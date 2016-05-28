import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Scanner;

/**
 * @author resry.lqy
 * @version $Id: Test.java, v 0.1 16/5/15 ионГ9:49 resry.lqy Exp $$
 */
public class Main {
    private void main() {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        BigInteger[] t = new BigInteger[201];
        t[0] = new BigInteger("1");
        t[1] = new BigInteger("1");
        for (int i = 2; i <= 200; i++) {
            t[i] = t[i-1].add(t[i-2]);
        }
        while (sc.hasNext()) {
            int n = sc.nextInt();
            System.out.println(t[n]);
        }
    }
    public static void main(String[] args) {
        new Main().main();
    }
}