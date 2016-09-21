import java.io.*;
import java.util.*;

public class RepeatString {
	private static final int INF = (int) 1e9 + 7;
	public int minimalModify(String s) {
		int res = INF;
		for (int middle = 0; middle < s.length(); ++middle) {
			String a = s.substring(0, middle);
			String b = s.substring(middle);
			res = Math.min(res, doit(a, b));
		}
		return res;
	}

	private int doit(String a, String b) {
		int[][] res = new int[a.length() + 1][b.length() + 1];

		for (int[] x: res) Arrays.fill(x, INF);
		res[0][0] = 0;
		for (int i = 0; i <= a.length(); ++i) {
			for (int j = 0; j <= b.length(); ++j) {
				if (i < a.length()) {
					res[i + 1][j] = Math.min(res[i + 1][j], res[i][j] + 1);
				}
				if (j < b.length()) {
					res[i][j + 1] = Math.min(res[i][j + 1], res[i][j] + 1);
				}
				if (i < a.length() && j < b.length()) {
					res[i + 1][j + 1] = Math.min(res[i + 1][j + 1], res[i][j] + (a.charAt(i) == b.charAt(j) ? 0 : 1));
				}
			}

		}
		return res[a.length()][b.length()];
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("RepeatString (250 Points)");
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
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1474417828;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s, int __expected) {
        s = new String(s);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		RepeatString instance = new RepeatString();
		int __result = 0;
		try {
			__result = instance.minimalModify(s);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 698/RepeatString.sample";
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
