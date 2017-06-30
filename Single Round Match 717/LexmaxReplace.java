import java.io.*;
import java.util.*;

public class LexmaxReplace {
	public String get(String s, String t) {
        int[] a = new int[26];
        for (int i = 0; i < t.length(); ++i) {
            a[t.charAt(i) - 'a']++;
        }
        for (int i = 25; i >= 0;) {
            if (a[i] > 0) {
                --a[i];

                String tmp = "";
                char ch = (char)('a' + i);
                for (int j = 0; j < s.length(); ++j) {
                    if (ch != '-' && ch > s.charAt(j)) {
                        tmp += ch;
                        ch = '-';
                    } else {
                        tmp += s.charAt(j);
                    }
                }
                s = tmp;
                if (ch != '-') {
                    return s;
                }
            }
            if (a[i] == 0) --i;
        }
		return s;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("LexmaxReplace (500 Points)");
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
            String t = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s, t, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1498824848;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s, String t, String __expected) {
        s = new String(s);
        t = new String(t);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		LexmaxReplace instance = new LexmaxReplace();
		String __result = "";
		try {
			__result = instance.get(s, t);
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
        private static final String dataFileName = "LexmaxReplace.sample";
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
