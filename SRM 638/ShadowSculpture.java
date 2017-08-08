import java.io.*;
import java.util.*;

public class ShadowSculpture {
	public String possible(String[] XY, String[] YZ, String[] ZX) {
		return "";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ShadowSculpture (300 Points)");
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

            String[] XY = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < XY.length; ++i)
                XY[i] = Reader.nextLine();
            String[] YZ = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < YZ.length; ++i)
                YZ[i] = Reader.nextLine();
            String[] ZX = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < ZX.length; ++i)
                ZX[i] = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(XY, YZ, ZX, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1502066821;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] XY, String[] YZ, String[] ZX, String __expected) {
		for (int i = 0; i < XY.length; i++) {
			XY[i] = new String(XY[i]);
		}
		for (int i = 0; i < YZ.length; i++) {
			YZ[i] = new String(YZ[i]);
		}
		for (int i = 0; i < ZX.length; i++) {
			ZX[i] = new String(ZX[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ShadowSculpture instance = new ShadowSculpture();
		String __result = "";
		try {
			__result = instance.possible(XY, YZ, ZX);
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
        private static final String dataFileName = "ShadowSculpture.sample";
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
