import java.io.*;
import java.util.*;

public class ShoppingSurveyDiv1 {
	public int minValue(int N, int K, int[] s) {
        int total = 0;
        for (int item : s) total += item;
        int res = 0;
        int small = N;
        while (total > small * (K - 1)) {
            ++res;//MUST GET ONE
            --small;
            for (int i = 0; i < s.length; ++i) if (s[i] > 0) {--s[i];--total;}//GET ALL TYPE ITEM
        }
		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ShoppingSurveyDiv1 (250 Points)");
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

            int N = Integer.parseInt(Reader.nextLine());
            int K = Integer.parseInt(Reader.nextLine());
            int[] s = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < s.length; ++i)
                s[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, K, s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1502674589;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int K, int[] s, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ShoppingSurveyDiv1 instance = new ShoppingSurveyDiv1();
		int __result = 0;
		try {
			__result = instance.minValue(N, K, s);
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
        private static final String dataFileName = "ShoppingSurveyDiv1.sample";
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
