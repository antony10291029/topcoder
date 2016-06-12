import java.io.*;
import java.lang.Integer;
import java.lang.RuntimeException;
import java.util.*;
import java.util.HashSet;

public class MultiplicationTable2 {
	public int minimalGoodSet(int[] table) {
		int[][] a = decode(table);
		int n = a.length;
		int min = n;
		for (int times = 0; times < n; ++times) {
			Set<Integer> set = new HashSet<Integer>();
			set.add(times);
			boolean upd = true;
			while (upd) {
				upd = false;
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < n; ++j) {
						if (set.contains(i) && set.contains(j) && !set.contains(a[i][j])) {
							upd = true;
							set.add(a[i][j]);
						}
					}
				}
			}
			min = Math.min(min, set.size());
		}
		return min;
	}
	private int[][] decode(int[] table) {
		for (int i = 1; i <= 50; ++i) {
			if (i * i == table.length) {
				int n = i;
				int[][] ret = new int[n][n];
				for (int r = 0; r < n; ++r) {
					for (int c = 0; c < n; ++c) {
						ret[r][c] = table[r*n + c];
					}
				}
				return ret;
			}
		}
		throw new RuntimeException("wrong number of elements");
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("MultiplicationTable2 (250 Points)");
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

            int[] table = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < table.length; ++i)
                table[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(table, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466942916;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] table, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		MultiplicationTable2 instance = new MultiplicationTable2();
		int __result = 0;
		try {
			__result = instance.minimalGoodSet(table);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 685/MultiplicationTable2.sample";
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
