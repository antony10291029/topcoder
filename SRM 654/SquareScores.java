import java.io.*;
import java.util.*;

public class SquareScores {
	public double calcexpectation(int[] p, String s) {
        double[] a = new double[26];
        for (int i = 0; i < p.length; ++i) {
            a[i] = p[i] / 100.0;
        }
        double res = 0.0;
        for (int si = 0; si < s.length(); ++si) {
            double[] b = new double[26];
            for (int j = 0; j < 26; ++j) {
                b[j] = 1.0;
            }
            for (int j = si; j < s.length(); ++j) {
                char ch = s.charAt(j);
                if (ch != '?') {
                    for (int k = 0; k < 26; ++k) {
                        if (ch != 'a' + k) {
                            b[k] *= 0.0;
                        } else {
                            b[k] *= 1.0;
                        }
                    }
                } else {
                    for (int k = 0; k < 26; ++k) {
                        b[k] *= a[k];
                    }
                }
                for (int k = 0; k < 26; ++k) {
                    res += b[k];
                }
            }
        }

		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("SquareScores (250 Points)");
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

            int[] p = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < p.length; ++i)
                p[i] = Integer.parseInt(Reader.nextLine());
            String s = Reader.nextLine();
            Reader.nextLine();
            double __answer = Double.parseDouble(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(p, s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1500689132;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] p, String s, double __expected) {
        s = new String(s);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		SquareScores instance = new SquareScores();
		double __result = 0.0;
		try {
			__result = instance.calcexpectation(p, s);
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
        private static final String dataFileName = "SquareScores.sample";
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
