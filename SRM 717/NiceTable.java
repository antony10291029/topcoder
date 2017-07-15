import java.io.*;
import java.util.*;

public class NiceTable {
	public String isNice(String[] t) {
        int R = t.length;
        int C = t[0].length();
        for (int i = 0; i < (1<<R); ++i) {
            for (int j = 0; j < (1<<C); ++j) {
                boolean ok = false;
                for (int k = 0; k < R; ++k) {
                    for (int k2 = 0; k2 < C; ++k2) {
                        int val1 = (i >> k) & 1;
                        int val2 = (j >> k2) & 1;
                        int val3 = val1 ^ val2;
                        int val4 = t[k].charAt(k2) - '0';
                        if (val3 != val4) ok = true;
                    }
                }
                if (!ok) return "Nice";
            }
        }
		return "Not nice";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("NiceTable (250 Points)");
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

            String[] t = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < t.length; ++i)
                t[i] = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(t, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1498823850;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] t, String __expected) {
		for (int i = 0; i < t.length; i++) {
			t[i] = new String(t[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		NiceTable instance = new NiceTable();
		String __result = "";
		try {
			__result = instance.isNice(t);
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
        private static final String dataFileName = "NiceTable.sample";
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
