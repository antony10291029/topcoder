import java.io.*;
import java.util.*;

public class FoxAirline2 {
    public String isPossible(int n, int[] a, int[] b) {
        int [][] e = new int[n][n];
		int edges = a.length;
		for (int i = 0; i < edges; ++i) {
			++e[a[i]][b[i]];
			++e[b[i]][a[i]];
		}
		int[][] c = new int[1<<n][n+1];
		int[] ones = new int[1<<n];
		for (int mask = 0; mask < (1<<n); ++mask) {
			for (int i = 0; i < n; ++i) {
				if (((mask >> i) & 1) == 0) {
					continue;
				}
				++ones[mask];
				for (int j = i + 1; j < n; ++j) {
					if (((mask >> j) & 1) == 0) {
						continue;
					}
					c[mask][1] += e[i][j];
				}
			}
		}
		for (int mask = 1; mask < (1 << n); ++mask) {
			for (int mask2 = 1; mask2 < (1 << n); ++mask2) {
				if ((mask & mask2) != 0) {
					continue;
				}
				for (int i = 1; i <= ones[mask]; ++i) {
					c[mask | mask2][i+1] = Math.max(c[mask | mask2][i+1], c[mask][i] + c[mask2][1]);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (edges - c[(1<<n) - 1][i] < 2 * (i - 1)) {
				return "Impossible";
			}
		}
		return "Possible";
    }

// CUT begin
	public static void main(String[] args){
		System.err.println("FoxAirline2 (450 Points)");
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

            int n = Integer.parseInt(Reader.nextLine());
            int[] a = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < a.length; ++i)
                a[i] = Integer.parseInt(Reader.nextLine());
            int[] b = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < b.length; ++i)
                b[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, a, b, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1465823672;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, int[] a, int[] b, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		FoxAirline2 instance = new FoxAirline2();
		String __result = "";
		try {
			__result = instance.isPossible(n, a, b);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 685/FoxAirline2.sample";
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
