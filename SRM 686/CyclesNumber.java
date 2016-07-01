import java.io.*;
import java.util.*;

public class CyclesNumber {
	private static final int M = 1000000007;
	private long[] fac = new long[100001];
	private ArrayList<ArrayList<Long>>  f = new ArrayList<ArrayList<Long>>();
	private long[][] st = new long[310][310];
	public int[] getExpectation(int[] n, int[] m) {
		int[] res = new int[n.length];
		for (int i = 0; i <= 300; ++i) {
			st[i][1] = st[i][i] = 1;
			for (int j = 2; j <= i - 1; ++j) {
				st[i][j] = (st[i-1][j-1] + j * st[i-1][j]) % M;
			}
		}
		fac[0] = 1;
		for (int i = 1; i <= 100000; ++i) {
			fac[i] = fac[i-1] *  i % M;
		}
		for (int i = 0; i <= 10000; ++i) {
			ArrayList<Long> listSub=new ArrayList<Long>();
			for (int j = 0; j <= 300; ++j) {
				listSub.add((long) 0);
			}
			f.add(listSub);
		}
		f.get(0).set(0, (long) 1);
		for (int i = 1; i <= 10000; ++i) {
			f.get(i).set(0, fac[i]);
			for (int j = 1; j <= 300; ++j) {
				f.get(i).set(j, f.get(i-1).get(j) * i % M + f.get(i-1).get(j-1) % M);
			}
		}
		for (int i = 0; i < n.length; ++i) {
			long sum = 0;
			for (int j = 0; j <= m[i]; ++j) {
				sum = (sum + f.get(n[i]).get(j) * fac[j] % M * st[m[i]][j] % M) % M;
			}
			res[i] = (int) sum;
		}
		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("CyclesNumber (600 Points)");
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

            int[] n = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < n.length; ++i)
                n[i] = Integer.parseInt(Reader.nextLine());
            int[] m = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < m.length; ++i)
                m[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, m, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1467250763;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] n, int[] m, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		CyclesNumber instance = new CyclesNumber();
		int[] __result = new int[0];
		try {
			__result = instance.getExpectation(n, m);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (equals(__result, __expected)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + toString(__expected));
			System.err.println("           Received: " + toString(__result));
			return false;
		}
	}

	static boolean equals(int[] a, int[] b) {
		if (a.length != b.length) return false;
		for (int i = 0; i < a.length; ++i) if (a[i] != b[i]) return false;
		return true;
	}

	static String toString(int[] arr) {
		StringBuffer sb = new StringBuffer();
		sb.append("[ ");
		for (int i = 0; i < arr.length; ++i) {
			if (i > 0) sb.append(", ");
			sb.append(arr[i]);
		}
		return sb.toString() + " ]";
	}

	static class Reader {
        private static final String dataFileName = "/Users/resry/topcoder/SRM 686/CyclesNumber.sample";
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
