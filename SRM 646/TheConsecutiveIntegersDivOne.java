import java.io.*;
import java.util.*;

public class TheConsecutiveIntegersDivOne {
    private int solve(int start, int[] a, int k) {
        int n = a.length;
        int res = 0x7f7f7f7f;
        for (int i = 0; i < n - k + 1; ++i) {
            int s = 0;
            for (int j = 0; j < k; ++j) {
                s += Math.abs(a[i+j] - (start+j));
            }
            res = Math.min(res, s);
        }
        return res;
    }
	public int find(int[] numbers, int k) {
        Arrays.sort(numbers);
        int N = numbers.length;
        int res = 0x7f7f7f7f;
        for (int i = 0; i < N; ++i) for (int d = -2*k; d <= 2*k; ++d) {
            res = Math.min(res, solve(numbers[i]+d, numbers, k));
        }
		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TheConsecutiveIntegersDivOne (250 Points)");
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

            int[] numbers = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < numbers.length; ++i)
                numbers[i] = Integer.parseInt(Reader.nextLine());
            int k = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(numbers, k, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1501408703;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] numbers, int k, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TheConsecutiveIntegersDivOne instance = new TheConsecutiveIntegersDivOne();
		int __result = 0;
		try {
			__result = instance.find(numbers, k);
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
        private static final String dataFileName = "TheConsecutiveIntegersDivOne.sample";
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
