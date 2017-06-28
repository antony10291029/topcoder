import java.io.*;
import java.util.*;

public class ConstructLCSEasy {
	public String construct(int ab, int bc, int ca) {
        int m1 = Math.max(ab, Math.max(bc, ca));
        int m3 = Math.min(ab, Math.min(bc, ca));
        int m2 = (ab + bc + ca) - m1 - m3;
        String A = "", B = "", C = "";
        for (int i = 0; i < m1; ++i) {
            A += "1";
            B += "1";
        }
        for (int i = 0; i < m2; ++i) {
            B += "0";
            C += "0";
        }
        for (int i = 0; i < m3; ++i) {
            A = "0" + A;
        }
        if (m1 == ab && m2 == bc && m3 == ca) {
             return A + " " + B + " " + C;
        } else if (m1 == ab && m2 == ca && m3 == bc) {
             return B + " " + A + " " + C;
        } else if (m1 == bc && m2 == ab && m3 == ca) {
             return C + " " + B + " " + A;
        } else if (m1 == bc && m2 == ca && m3 == ab) {
             return A + " " + C + " " + B;
        } else if (m1 == ca && m2 == ab && m3 == bc) {
             return A + " " + C + " " + B;
        } else if (m1 == ca && m2 == bc && m3 == ab) {
             return A + " " + C + " " + B;
        }
         return A + " " + C + " " + B;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ConstructLCSEasy (500 Points)");
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

            int ab = Integer.parseInt(Reader.nextLine());
            int bc = Integer.parseInt(Reader.nextLine());
            int ca = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(ab, bc, ca, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1498526669;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int ab, int bc, int ca, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ConstructLCSEasy instance = new ConstructLCSEasy();
		String __result = "";
		try {
			__result = instance.construct(ab, bc, ca);
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
        private static final String dataFileName = "ConstructLCSEasy.sample";
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
