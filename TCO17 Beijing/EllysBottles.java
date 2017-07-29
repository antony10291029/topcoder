import java.io.*;
import java.util.*;

public class EllysBottles {
	public double getVolume(int[] bottles, int k) {
        double[] b = new double[bottles.length];
        for (int i = 0; i < b.length; ++i) {
            b[i] = bottles[i];
        }
        for (int it = 0; it < Math.min(k, 1000000); ++it) {
            int maxAt = -1, minAt = -1;
            for (int i = 0; i < b.length; ++i) {
                if (maxAt == -1 || b[i] > b[maxAt]) maxAt = i;
                if (minAt == -1 || b[i] < b[minAt]) minAt = i;
            }
            if (b[maxAt] - b[minAt] < 1e-12) break;
            double avg = (b[maxAt] + b[minAt]) * 0.5;
            b[maxAt] = b[minAt] = avg;
        }
        Arrays.sort(b);
        return b[0];
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("EllysBottles (250 Points)");
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

            int[] bottles = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < bottles.length; ++i)
                bottles[i] = Integer.parseInt(Reader.nextLine());
            int k = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            double __answer = Double.parseDouble(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(bottles, k, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1501305753;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] bottles, int k, double __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		EllysBottles instance = new EllysBottles();
		double __result = 0.0;
		try {
			__result = instance.getVolume(bottles, k);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (doubleEquals(__expected, __result)) {
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

	static boolean doubleEquals(double a, double b) {
	    return !Double.isNaN(a) && !Double.isNaN(b) && Math.abs(b - a) <= 1e-9 * Math.max(1.0, Math.abs(a) );
	}

	static class Reader {
        private static final String dataFileName = "EllysBottles.sample";
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
