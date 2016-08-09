import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class DivisibleSetDiv1 {
	public String isPossible(int[] b) {
		BigInteger bigInteger = BigInteger.ONE;
		for (int x : b) {
			bigInteger = bigInteger.multiply(BigInteger.valueOf(x + 1));
		}
		BigInteger num = BigInteger.ZERO;
		for (int x : b) {
			num = num.add(bigInteger.divide(BigInteger.valueOf(x + 1)));
		}
		int cmp = num.compareTo(bigInteger);
		if (cmp > 0) {
			return "Impossible";
		}
		if (cmp < 0) {
			return "Possible";
		}
		for (int i = 0; i < b.length; ++i) {

			for (int j = i + 1; j < b.length; ++j) {

				if (b[i] == b[j]) {

					return "Impossible";
				}
			}
		}
		return "Possible";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("DivisibleSetDiv1 (300 Points)");
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

            int[] b = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < b.length; ++i)
                b[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(b, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1470680918;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] b, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		DivisibleSetDiv1 instance = new DivisibleSetDiv1();
		String __result = "";
		try {
			__result = instance.isPossible(b);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 697/DivisibleSetDiv1.sample";
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
