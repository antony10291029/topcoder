import java.io.*;
import java.util.*;

public class TopologicalOrdering {
	static int div;
	static List<Integer> stack;
	public int[] construct(int n) {
		if (stack != null) stack.clear();
		stack = null;
		int v = 0;
		List<Integer> ans = new ArrayList<Integer>();
		List<Integer> connect = new ArrayList<Integer>();
		stack = new ArrayList<Integer>();
		for (div = 2; div <= n; ++div) {
			while (n % div == 0) {
				n /= div;
				if (!go(1, 1)) {
					throw new AssertionError();
				}
				if (v > 0) {
					int conn = connect.get(v - 1);
					for (int j = 0; j < conn; ++j) {
						ans.add(v);
						ans.add(v - 1 - j);
					}
				}
				connect.add(1);
				++v;
				for (int i = stack.size() - 1; i >= 0; --i) {
					int cur = stack.get(i);
					for (int j = 0; j < cur - 1; ++j) {
						int conn = connect.get(v - 1);
						for (int k = 0; k < conn; ++k) {
							ans.add(v);
							ans.add(v - 1 - k);
						}
						connect.add(1);
						++v;
					}
					if (v > cur) {
						int conn = connect.get(v - cur - 1);
						for (int j = 0; j < conn; ++j) {
							ans.add(v);
							ans.add(v - cur - 1 - j);
						}
					}
					connect.add(2);
					++v;

				}
				stack.clear();
			}
		}
		if (v == 0) {
			v = 1;
		}
		if (v > 50 || ans.size() > 200) {
			throw  new AssertionError();
		}
		int res[] = new int[ans.size() + 1];
		res[0] = v;
		for (int i = 1; i < res.length; ++i) {
			res[i] = ans.get(i - 1);
		}
		return res;
	}
	static boolean go(int cur, int prev) {
		if (cur == div) {
			return true;
		}
		if (cur > div) {
			return false;
		}
		for (int i = 1; i <= 3; ++i) {
			if (go(i * cur + prev, cur)) {
				stack.add(i);
				return true;
			}
		}
		return false;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TopologicalOrdering (1000 Points)");
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
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1471012559;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TopologicalOrdering instance = new TopologicalOrdering();
		int[] __result = new int[0];
		try {
			__result = instance.construct(n);
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
        private static final String dataFileName = "/Users/resry/topcoder/TCO 2016 Round 3A/TopologicalOrdering.sample";
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
