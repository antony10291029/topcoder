import java.io.*;
import java.util.*;

public class LCMGCD {
    private static final String YES = "Possible";
    private static final String NO = "Impossible";
    int n;
    int signum(int x) {
        if (x == 0) return 0;
        return x > 0 ? 1 : -1;
    }
    int cmp(int x, int y) {
        return 1 + signum(x - y);
    }
    boolean can(int[][] a) {
		if (a[1][1] > 0) {
		  if (a[0][2] != 0 && n == a[0][2] + 1) return false;
		  if (a[2][0] != 0 && n == a[2][0] + 1) return false;
		  return true;
		}
		if (a[0][1] > 0 && a[1][0] > 0) {
		  return true;
		}
		if (a[2][1] > 0 && a[1][2] > 0) {
		  return true;
		}
		if (a[2][1] > 0 && a[1][0] > 0) {
		  if (a[0][2] > 0) return true;
		  return false;
		}
		if (a[0][1] > 0 && a[1][2] > 0) {
		  if (a[2][0] > 0) return true;
		  return false;
		}
		return false;
    }
	public String isPossible(int[] x, int t) {
        int[][] a = new int[3][3];
        this.n = x.length;
        Pair o = new Pair(t);
        for (int val : x) {
            Pair pair = new Pair(val);
            ++a[cmp(o.x, pair.x)][cmp(o.y, pair.y)];
        }
		return can(a) ? YES : NO;
	}
    static class Pair {
        int x, y;
        public Pair(){}
        public Pair(int val) {
            x = y = 0;
            while (val % 2 == 0 && val != 1) {
                val /= 2;
                ++x;
            }
            while (val % 3 == 0 && val != 1) {
                val /= 3;
                ++y;
            }
        }
    }

// CUT begin
	public static void main(String[] args){
		System.err.println("LCMGCD (400 Points)");
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
            int t = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(x, t, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1499514490;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 400 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] x, int t, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		LCMGCD instance = new LCMGCD();
		String __result = "";
		try {
			__result = instance.isPossible(x, t);
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
        private static final String dataFileName = "LCMGCD.sample";
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
