import java.io.*;
import java.util.*;

public class TrianglesContainOrigin {
	public long count(int[] x, int[] y) {
        int n = x.length;
        double[] angle = new double[2 * n];
        for (int i = 0; i < n; ++i) {
            angle[i] = Math.atan2(y[i], x[i]);
            angle[i+n] = angle[i] + 2 * Math.PI;
        }
        Arrays.sort(angle);
        int diff = 0;
        long res = 1L * n * (n - 1) * (n - 2) / (3 * 2 * 1);
        for (int i = 0; i < n; ++i) {
            while (diff + 1 < 2 * n && angle[diff + 1] < angle[i] + Math.PI) ++diff;
            int cnt = diff - i;
            res -= 1L * cnt * (cnt - 1) / (2 * 1);
        }
		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TrianglesContainOrigin (250 Points)");
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

            int[] x = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < x.length; ++i)
                x[i] = Integer.parseInt(Reader.nextLine());
            int[] y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < y.length; ++i)
                y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(x, y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1501904757;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] x, int[] y, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TrianglesContainOrigin instance = new TrianglesContainOrigin();
		long __result = 0;
		try {
			__result = instance.count(x, y);
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
        private static final String dataFileName = "TrianglesContainOrigin.sample";
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
