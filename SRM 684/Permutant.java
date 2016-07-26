import java.io.*;
import java.util.*;

public class Permutant {
    private static final long MOD = (long) (1e9 + 7);

    public int counthis(int[] a) {
        Arrays.sort(a);
        long mult = 1;
        for (int x : a) {
            for (int i = 1; i < x; ++i) {
                mult = mult * i % MOD;
            }
        }
        int s = 0;
        for (int x : a) {
            s += x;
        }
        long[][] c = new long[s + 1][s + 1];
        c[0][0] = 1;
        for (int n = 1; n <= s; ++n) {
            c[n][0] = 1;
            for (int k = 1; k <= s; ++k) {
                c[n][k] = c[n - 1][k - 1] + c[n - 1][k];
                if (c[n][k] > MOD)
                    c[n][k] -= MOD;
            }
        }
        long[] ways = new long[s + 1];
        long[] nways = new long[s + 1];
        long res = 0;

        for (int magic = 0; magic < a.length; ++magic) {
            int cs = a[magic];
            Arrays.fill(ways, 0, cs, 0);
            ways[0] = a[magic];
            for (int i = 0; i < a.length; ++i) {
                if (i != magic) {
                    int cur = a[i];
                    int ns = cs + cur;
                    Arrays.fill(nways, 0, ns, 0);
                    for (int left = 1; left <= cur; ++left) {
                        int right = cur - left;
                        for (int old = 0; old < cs; ++old) {
                            long ow = ways[old];
                            if (ow == 0)
                                continue;
                            nways[old + left] = (nways[old + left] + ow
                                                                     * c[old + left][left]
                                                                     % MOD
                                                                     * c[cs - 1 - old + right][right])
                                                % MOD;
                        }
                    }

                    long[] tmp = ways;
                    ways = nways;
                    nways = tmp;
                    cs = ns;
                }
            }
            long sum = 0;
            for (long x : ways)
                sum += x;
            sum %= MOD;
            res = (res + sum) % MOD;
        }
        return (int) (res * mult % MOD);
    }

    // CUT begin
    public static void main(String[] args) {
        System.err.println("Permutant (1000 Points)");
        System.err.println();
        HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i)
            cases.add(Integer.parseInt(args[i]));
        runTest(cases);
    }

    static void runTest(HashSet<Integer> caseSet) {
        int cases = 0, passed = 0;
        while (true) {
            String label = Reader.nextLine();
            if (label == null || !label.startsWith("--"))
                break;

            int[] a = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < a.length; ++i)
                a[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
            System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(a, __answer))
                passed++;
        }
        if (caseSet.size() > 0)
            cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int) (System.currentTimeMillis() / 1000) - 1469493129;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points",
            T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
    }

    static boolean doTest(int[] a, int __expected) {
        long startTime = System.currentTimeMillis();
        Throwable exception = null;
        Permutant instance = new Permutant();
        int __result = 0;
        try {
            __result = instance.counthis(a);
        } catch (Throwable e) {
            exception = e;
        }
        double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

        if (exception != null) {
            System.err.println("RUNTIME ERROR!");
            exception.printStackTrace();
            return false;
        } else if (__result == __expected) {
            System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
            return true;
        } else {
            System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
            System.err.println("           Expected: " + __expected);
            System.err.println("           Received: " + __result);
            return false;
        }
    }

    static class Reader {
        private static final String   dataFileName = "/Users/resry/topcoder/SRM 684/Permutant.sample";
        private static BufferedReader reader;

        public static String nextLine() {
            try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(
                        dataFileName)));
                }
                return reader.readLine();
            } catch (IOException e) {
                System.err.println("FATAL!! IOException");
                e.printStackTrace();
                System.exit(1);
            }
            return "";
        }
    }
    // CUT end
}
