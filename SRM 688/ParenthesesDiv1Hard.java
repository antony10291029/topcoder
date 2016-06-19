import java.io.*;
import java.util.*;

public class ParenthesesDiv1Hard {
    private static class Pair {
        int cost;
        int depth;
    }

    private int[] a;

    public int minCost(String s) {
        this.a = new int[s.length()];
        int sum = 0;
        for (int i = 0; i < a.length; ++i) {
            if (s.charAt(i) == '(') {
                a[i] = 1;
            } else {
                a[i] = -1;
            }
            sum += a[i];
            if (sum < 0) {
                return -1;
            }
        }
        if (sum != 0) {
            return -1;
        }
        Pair[] res = rec(0, a.length - 1, 0);
        int ans = res[0].cost + res[1].cost;
        return ans;
    }

    private Pair[] rec(int left, int right, int side) {
        Pair[] res = new Pair[2];
        res[0] = new Pair();
        res[1] = new Pair();
        int prev = left;
        while (prev < right) {
            int sum = 0;
            int next = prev;
            do {
                sum += a[next++];
            } while (sum != 0);
            Pair[] tmp = rec(prev + 1, next - 2, 1 - side);
            res[side].cost += (tmp[side].depth + 1) * (tmp[side].depth + 1) + tmp[side].cost;
            res[side].depth = Math.max(res[side].depth, 1 + tmp[side].depth);

            res[1 - side].cost += tmp[1 - side].cost;
            res[1 - side].depth = Math.max(res[1 - side].depth, tmp[1 - side].depth);
            prev = next;
        }
        return res;
    }

// CUT begin
	public static void main(String[] args){
		System.err.println("ParenthesesDiv1Hard (1000 Points)");
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
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466338094;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s, int __expected) {
        s = new String(s);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ParenthesesDiv1Hard instance = new ParenthesesDiv1Hard();
		int __result = 0;
		try {
			__result = instance.minCost(s);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 688/ParenthesesDiv1Hard.sample";
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
