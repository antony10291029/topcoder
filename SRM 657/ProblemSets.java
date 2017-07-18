import java.io.*;
import java.util.*;

public class ProblemSets {
    private boolean f(long e, long em, long m, long mh, long h, long gap) {
        if (gap > e + em) return false;
        if (gap > h + mh) return false;
        em -= Math.max((long) 0, gap - e);
        mh -= Math.max((long) 0, gap - h);
        return (m + em + mh) >= gap;

    }
	public long maxSets(long E, long EM, long M, long MH, long H) {
        long l = 0, r = Long.MAX_VALUE;
        while (l + 1 < r) {
            long m = l + (r - l) / 2;
            if (f(E, EM, M, MH, H, m)) {
                l = m;
            } else {
                r = m;
            }
        }
		return l;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ProblemSets (250 Points)");
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

            long E = Long.parseLong(Reader.nextLine());
            long EM = Long.parseLong(Reader.nextLine());
            long M = Long.parseLong(Reader.nextLine());
            long MH = Long.parseLong(Reader.nextLine());
            long H = Long.parseLong(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(E, EM, M, MH, H, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1500341561;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(long E, long EM, long M, long MH, long H, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ProblemSets instance = new ProblemSets();
		long __result = 0;
		try {
			__result = instance.maxSets(E, EM, M, MH, H);
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
        private static final String dataFileName = "ProblemSets.sample";
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
