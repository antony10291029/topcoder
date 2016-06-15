import java.io.*;
import java.util.*;

public class AlmostFibonacciKnapsack {
	private long[] f = new long[999];
	public int[] getIndices(long x) {
		int n = 2;
		f[1] = 1;
		f[2] = 2;
		while (f[n] <= x) {
			++n;
			f[n] = f[n-1] + f[n-2];
		}
		for (int cnt = 1; cnt <= n; ++cnt) {
			long a = x - cnt;
			if (a < 1) {
				continue;
			}
			int total = 0;
			int[] b = new int[n+1];
			for (int i = n; i >= 1; --i) {
				if (a >= f[i]) {
					b[i] = 1;
					a -= f[i];
					++total;
				} else {
					b[i] = 0;
				}
			}
			if (total > cnt) {
				continue;
			}
			while (total < cnt) {
				for (int i = 3; i <= n; ++i) {
					if (b[i - 2] == 0 && b[i - 1] == 0 && b[i] == 1) {
						b[i] = 0;
						b[i - 2] = b[i - 1] = 1;
						++total;
						break;
					}
				}
			}
			if (total == cnt) {
				int[] res = new int[cnt];
				int ct = 0;
				for (int i = 1; i <= n; ++i) {
					if (b[i] == 1) {
						res[ct++] = i;
					}
				}
				return res;
			}
		}
		return new int[0];
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("AlmostFibonacciKnapsack (250 Points)");
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

            long x = Long.parseLong(Reader.nextLine());
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(x, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1467445607;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(long x, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		AlmostFibonacciKnapsack instance = new AlmostFibonacciKnapsack();
		int[] __result = new int[0];
		try {
			__result = instance.getIndices(x);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (equals(__result, __expected)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + toString(__expected));
			System.err.println("           Received: " + toString(__result));
			return false;
		}
	}

	static boolean equals(int[] a, int[] b) {
		if (a.length != b.length) return false;
		for (int i = 0; i < a.length; ++i) if (a[i] != b[i]) return false;
		return true;
	}

	static String toString(int[] arr) {
		StringBuffer sb = new StringBuffer();
		sb.append("[ ");
		for (int i = 0; i < arr.length; ++i) {
			if (i > 0) sb.append(", ");
			sb.append(arr[i]);
		}
		return sb.toString() + " ]";
	}

	static class Reader {
        private static final String dataFileName = "/Users/resry/topcoder/SRM 687/AlmostFibonacciKnapsack.sample";
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
