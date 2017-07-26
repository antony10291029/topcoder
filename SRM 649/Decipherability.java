import java.io.*;
import java.util.*;

public class Decipherability {
	public String check(String s, int K) {
        int n = s.length();
        boolean[][][][] dp = new boolean[2][n+1][n+1][n+1];
        dp[0][0][0][0] = true;
        for (int i = 0; i < 2; ++i) for (int length = 0; length < n; ++length) for(int x = 0; x <= n; ++x) for (int y = 0; y <= n; ++y) {
            if (dp[i][length][x][y] == false) continue;
            if (x < n) dp[i][length][x+1][y] = true;
            if (y < n) dp[i][length][x][y+1] = true;
            if (x < n && y < n && s.charAt(x) == s.charAt(y)) {
                int j = i;
                if (x != y) j = 1;
                dp[j][length+1][x+1][y+1] = true;
            }
        }
        for (int x = 0; x <= n; ++x) for (int y = 0; y <= n; ++y) {
            if (dp[1][n-K][x][y] == true) {
                return "Uncertain";
            }
        }
		return "Certain";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("Decipherability (250 Points)");
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
            int K = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s, K, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1501032157;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s, int K, String __expected) {
        s = new String(s);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		Decipherability instance = new Decipherability();
		String __result = "";
		try {
			__result = instance.check(s, K);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__expected.equals(__result)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + "\"" + __expected + "\"");
			System.err.println("           Received: " + "\"" + __result + "\"");
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "Decipherability.sample";
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
