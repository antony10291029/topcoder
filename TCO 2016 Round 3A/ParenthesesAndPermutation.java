import java.io.*;
import java.util.*;

public class ParenthesesAndPermutation {
	public static final String IMP = "Impossible";
	public String getSequence(int[] p) {
		int n= p.length;
		boolean[] was = new boolean[n];
		int curL = 0;
		boolean[] tOpen = new boolean[n];
		for (int len = 1; len <= n; len += 2) {
			while (curL < len) {
				was[p[curL]] = true;
				curL++;
			}
			for (int i = 0; i < n; ++i) {
				if (was[i]) {
					tOpen[i] = true;
					was[i] = false;
					break;
				}
			}
		}
		int c = 0;
		for (int i = 0; i < n; ++i) {
			if (tOpen[i]) {
				c++;
			} else {
				c--;
			}
			if (c < 0) return IMP;
		}
		char[] res = new char[n];
		for (int i = 0; i < n; ++i) {
			res[i] = tOpen[p[i]] ? '(' : ')';
		}
		return new String(res);
	}


// CUT begin
	public static void main(String[] args){
		System.err.println("ParenthesesAndPermutation (250 Points)");
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

            int[] p = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < p.length; ++i)
                p[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(p, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1472294893;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] p, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ParenthesesAndPermutation instance = new ParenthesesAndPermutation();
		String __result = "";
		try {
			__result = instance.getSequence(p);
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
        private static final String dataFileName = "/Users/resry/topcoder/TCO 2016 Round 3A/ParenthesesAndPermutation.sample";
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
