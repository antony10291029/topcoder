import java.io.*;
import java.util.*;

public class OkonomiyakiParty {
    private static final int MOD = (int)(1e9 + 7.1);
	public int count(int[] osize, int M, int K) {
        long dp[][] = new long[64][64];
        dp[0][0] = 1L;
        for (int i = 0; i < 63; ++i) for (int j=0; j < i+1; ++j) {
            if (i == 0) continue;
            dp[i][j] = (j==0?1:dp[i-1][j] + dp[i-1][j-1]);
        }
        Arrays.sort(osize);
        long res = 0;
        int n = osize.length;
        for (int i = 0; i < n; ++i) {
            int maxSize = osize[i] + K;
            int maxIndex = i;
            for (int j = i; j < n; ++j) {
                if (osize[j] <= maxSize) maxIndex = j;
            }
            int ct = (maxIndex - i);
            if (ct < M - 1) continue;
            res = (res + dp[ct][M-1]) % MOD;
        }
		return (int) res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("OkonomiyakiParty (250 Points)");
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

            int[] osize = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < osize.length; ++i)
                osize[i] = Integer.parseInt(Reader.nextLine());
            int M = Integer.parseInt(Reader.nextLine());
            int K = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(osize, M, K, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1501463154;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] osize, int M, int K, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		OkonomiyakiParty instance = new OkonomiyakiParty();
		int __result = 0;
		try {
			__result = instance.count(osize, M, K);
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
        private static final String dataFileName = "OkonomiyakiParty.sample";
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
