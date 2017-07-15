import java.io.*;
import java.util.*;

public class InterleavingParenthesis {
    private static int MOD = 1000_000_007;
    int[][] dp;
	public int countWays(String s1, String s2) {
        int n = s1.length();
        int m = s2.length();
        dp = new int[s1.length() + 1][s2.length() + 1];
        int[] a = new int[s1.length() + 1];
        int[] b = new int[s2.length() + 1];
        for (int i = 1; i < s1.length() + 1; ++i) {
            if (s1.charAt(i - 1) == '(') a[i] = a[i - 1] + 1;
            else a[i] = a[i - 1] - 1;
        }
        for (int i = 1; i < s2.length() + 1; ++i) {
            if (s2.charAt(i - 1) == '(') b[i] = b[i - 1] + 1;
            else b[i] = b[i - 1] - 1;
        }
        dp[0][0] = 1;
        for (int i = 0; i < s1.length() + 1; ++i) {
            for (int j = 0; j < s2.length() + 1; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                dp[i][j] = 0;
                if (a[i] + b[j] < 0) continue;
                if (i > 0) dp[i][j] = dp[i-1][j];
                if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
		return dp[n][m];
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
