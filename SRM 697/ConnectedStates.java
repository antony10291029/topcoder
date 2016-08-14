import java.io.*;
import java.util.*;

public class ConnectedStates {
	private static int MOD = (int) (1e9 + 7);
	public int getSum(int[] a) {
		int n = a.length;
		int[] p = new int[n - 1];
		p[0] = 1;
		int sum = 0;
		int prod = 1;
		for (int x : a) {
			for (int i = n - 2; i >= 1; --i) {
				p[i] = (int) ((p[i] + (long) x * p[i - 1]) % MOD);
			}
			sum = (sum + x) % MOD;
			prod = (int) ((long) prod * x % MOD);
		}
		int[] inv = new int[n - 1];
		inv[0] = 0;
		if (inv.length > 1) {
			inv[1] = 1;
		}
		for (int i = 2; i < inv.length; ++i) {
			inv[i] = MOD - (int) ((long) (MOD / i) * inv[MOD % i] % MOD);
		}
		int[] exp = new int[n - 1];
		exp[0] = prod;
		for (int i = 1; i <= n - 2; ++i) {
			exp[i] = (int) ((long) exp[i - 1] * sum % MOD * inv[i] % MOD);
		}
		int ret = 0;
		for (int i = 0; i <= n - 2; ++i) {
			ret += (int) ((long) p[i] * exp[n - 2 - i] % MOD);
			ret %= MOD;
		}
		for (int i = 1; i <= n - 2; ++i) {
			ret = (int) ((long)ret * i % MOD);
		}
		return ret;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ConnectedStates (1000 Points)");
		System.err.println();
		HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
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
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1471155112;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] a, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ConnectedStates instance = new ConnectedStates();
		int __result = 0;
		try {
			__result = instance.getSum(a);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "/Users/resry/topcoder/SRM 697/ConnectedStates.sample";
	    private static BufferedReader reader;

	    public static String nextLine() {
	        try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
	        }
	        catch (IOException e) {
	            System.err.println("FATAL!! IOException");
	            e.printStackTrace();
	            System.exit(1);
	        }
	        return "";
	    }
	}
// CUT end
}
