import java.io.*;
import java.util.*;

public class BracketSequenceDiv1 {
	private long[][][] dp = new long[2][45][45];
	private String s = null;
	public long calc(int has, int l, int r)  {
		if (l >= r) {
			return has;
		}
		long res = dp[has][l][r];
		if (res != -1) {
			return res;
		}
		res = calc(has, l + 1, r);
		if (s.charAt(l) == '[' || s.charAt(l) == '(') {
			for (int i = l + 1; i <= r; ++i) {
				if (s.charAt(l) == '[' && s.charAt(i) == ']') {
					res += calc(1, l+1, i-1) * calc(1, i + 1, r);
				}
				if (s.charAt(l) == '(' && s.charAt(i) == ')') {
					res += calc(1, l+1, i-1) * calc(1, i+1, r);
				}
			}
		}
		dp[has][l][r] = res;
		return res;
	}
	public long count(String ss) {
		s = ss;
		int n = s.length();
		for (int ii = 0; ii < 2; ++ii) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					dp[ii][i][j] = -1;
				}
			}
		}
		return calc(0, 0, n - 1);
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("BracketSequenceDiv1 (300 Points)");
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

            String s = Reader.nextLine();
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1467247315;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s, long __expected) {
        s = new String(s);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		BracketSequenceDiv1 instance = new BracketSequenceDiv1();
		long __result = 0;
		try {
			__result = instance.count(s);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 686/BracketSequenceDiv1.sample";
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
