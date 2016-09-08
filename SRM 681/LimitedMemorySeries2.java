import java.io.*;
import java.util.*;

public class LimitedMemorySeries2 {
	public static long a;
	public static long b;
	public static final long mod = 1L << 50;
	public int getSum(int n, long x0, long aa, long bb) {
		long total = 0;
		long x = x0;
		a = aa;
		b = bb;
		List<Long> stack = new ArrayList<Long>();//decresing
		List<Long> caps = new ArrayList<Long>();//max radius
		List<Long> positions = new ArrayList<Long>();

		stack.add(x0);
		caps.add(0L);
		positions.add(0L);

		for (int i = 1; i < n; ++i) {
			x = right(x);
			long cap = 0;
			long lastY = -1;
			while (stack.size() > 0 && stack.get(stack.size() - 1) <= x) {
				long y = stack.remove(stack.size() - 1);
				long pos = positions.remove(positions.size() - 1);
				if (y < x) cap = (i - pos);
				lastY = y;
				long radius = Math.min(caps.remove(caps.size() - 1), i - pos - 1);
				total += radius;
			}
			if (lastY != -1)
			while (cap < i && left(lastY) < x) {
				lastY = left(lastY);
				cap += 1;
			}
			stack.add(x);
			caps.add(cap);
			positions.add((long) i);
		}
		while (stack.size() > 0) {
			stack.remove(stack.size() - 1);
			long pos = positions.remove(positions.size() - 1);
			long radius = Math.min(caps.remove(caps.size() - 1), n - 1 - pos);
			total += radius;
		}
		return (int) (total % (int)(1e9 + 7));
	}
	long right(long x) {
		return ((x ^ a) + b) & (mod - 1);
	}
	long left(long x) {
		x |= mod;
		x -= b;
		x ^= a;
		return x & (mod - 1);
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("LimitedMemorySeries2 (500 Points)");
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

            int n = Integer.parseInt(Reader.nextLine());
            long x0 = Long.parseLong(Reader.nextLine());
            long a = Long.parseLong(Reader.nextLine());
            long b = Long.parseLong(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, x0, a, b, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1473293404;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, long x0, long a, long b, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		LimitedMemorySeries2 instance = new LimitedMemorySeries2();
		int __result = 0;
		try {
			__result = instance.getSum(n, x0, a, b);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 681/LimitedMemorySeries2.sample";
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
