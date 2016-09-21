import java.io.*;
import java.util.*;

public class IntersectingConvexHull {
	private static final long MODULO = (long) (1e9 + 7);

	public int count(int[] x, int[] y) {
		long [][] comb = new long[x.length + 1][y.length + 1];
		comb[0][0] = 1;
		for (int i = 1; i <= x.length; ++i) {
			comb[i][0] = 1;
			for (int j = 1; j <= x.length; ++j) {
				comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODULO;
			}
		}
		long total = 0;
		for (int a = 3; a <= x.length; ++a) {
			for (int b = 3; a + b <= x.length; ++b) {
				total = (total + comb[x.length][a] * comb[x.length - a][b]) % MODULO;
			}
		}
		return (int) ((total - contDisjoint(x, y, comb) + MODULO) % MODULO);
	}

	private long contDisjoint(int[] x, int[] y, long[][] comb) {
		long res = 0;
		long[] overall = new long[x.length + 1];
		for (int a = 2; a <= x.length; ++a) {
			for (int b = 2; b <= a; ++b) {
				overall[a] = (overall[a] + comb[a][b]) % MODULO;
			}
		}
		for (int a = 0; a < x.length; ++ a) {
			for (int b = 0; b < x.length; ++b) {
				if (a != b) {
					int va = 0;
					int vb = 0;
					for (int c = 0; c < x.length; ++c) {
						if (c == a || c == b) continue;
						if ((x[c] - x[a]) * (long) (y[b] - y[a]) - (x[b] - x[a]) * (long) (y[c] - y[a]) > 0) {
							++va;
						} else {
							++vb;
						}
					}
					res += overall[va] * overall[vb];
					res %= MODULO;
				}
			}
		}
		return res;
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("IntersectingConvexHull (500 Points)");
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

            int[] x = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < x.length; ++i)
                x[i] = Integer.parseInt(Reader.nextLine());
            int[] y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < y.length; ++i)
                y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(x, y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1474420492;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] x, int[] y, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		IntersectingConvexHull instance = new IntersectingConvexHull();
		int __result = 0;
		try {
			__result = instance.count(x, y);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 698/IntersectingConvexHull.sample";
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
