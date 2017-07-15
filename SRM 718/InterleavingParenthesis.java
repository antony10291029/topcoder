import java.io.*;
import java.util.*;

public class InterleavingParenthesis {
    private static int MOD = 1000_000_007;
    int[][][] dp;
    String x, y;
    public int f(int a, int b, int sum) {
        if (a >= x.length() && b >= y.length()) {
            if (sum == 0) return 1;
            return 0;
        }
        if (dp[a][b][sum] >= 0) return dp[a][b][sum];
        int s = 0;
        if (a < x.length()) {
            if (x.charAt(a) == '(') s = (s + f(a + 1, b, sum + 1)) % MOD;
            else if (sum > 0) s = (s + f(a + 1, b, sum - 1)) % MOD;
        }
        if (b < y.length()) {
            if (y.charAt(b) == '(') s = (s + f(a, b + 1, sum + 1)) % MOD;
            else if (sum > 0) s = (s + f(a, b + 1, sum - 1)) % MOD;
        }
        dp[a][b][sum] = s;
        return s;
    }
	public int countWays(String s1, String s2) {
        x = s1;
        y = s2;
        dp = new int[s1.length() + 1][s2.length() + 1][s1.length() + s2.length() + 1];
        for (int i = 0; i < s1.length() + 1; ++i) {
            for (int j = 0; j < s2.length() + 1; ++j) {
                for (int k = 0; k < s1.length() + s2.length() + 1; ++k) {
                    dp[i][j][k] = -1;
                }
            }
        }
		return f(0, 0, 0);
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("InterleavingParenthesis (250 Points)");
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

            String s1 = Reader.nextLine();
            String s2 = Reader.nextLine();
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s1, s2, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1500105392;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s1, String s2, int __expected) {
        s1 = new String(s1);
        s2 = new String(s2);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		InterleavingParenthesis instance = new InterleavingParenthesis();
		int __result = 0;
		try {
			__result = instance.countWays(s1, s2);
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
        private static final String dataFileName = "InterleavingParenthesis.sample";
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
