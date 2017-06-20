import java.io.*;
import java.util.*;

public class ABBADiv1 {
    private boolean can(String x, String y) {
        if (x == null || y == null) {
            return x == null ? y == null : x == null;
        }
        if (x != null && x.equals(y)) {
            return true;
        }
        if (x.length() == y.length()) {
            return false;
        }
        if (y.charAt(y.length() - 1) == 'A' && can(x, y.substring(0, y.length() - 1))) {
            return true;
        }
        if (y.charAt(0) == 'B' && can(x, reverse(y.substring(1)))) {
            return true;
        }
        return false;
    }
    private String reverse(String t) {
        StringBuilder sb = new StringBuilder(t);
        return sb.reverse().toString();
    }
	public String canObtain(String initial, String target) {
		return can(initial, target)?"Possible":"Impossible";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ABBADiv1 (300 Points)");
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

            String initial = Reader.nextLine();
            String target = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(initial, target, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1497919202;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String initial, String target, String __expected) {
        initial = new String(initial);
        target = new String(target);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ABBADiv1 instance = new ABBADiv1();
		String __result = "";
		try {
			__result = instance.canObtain(initial, target);
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
        private static final String dataFileName = "ABBADiv1.sample";
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
