import java.io.*;
import java.util.*;

public class HardProof {
	public int minimumCost(int[] D) {
		int ret = Integer.MAX_VALUE;
		int n = 0;
		while (n * n < D.length) ++n;
		Set<Integer> s = new TreeSet<Integer>();
		for (int item : D) {
			s.add(item);
		}
		ArrayList<Integer> all = new ArrayList<Integer>();
		for (int item : s) {
			all.add(item);
		}
		for (int i = 0, j = 0; i < all.size(); ++i) {
			while (j < all.size()) {
				LinkedList<Integer>[] edges = new LinkedList[n];
				LinkedList<Integer>[] edgesR = new LinkedList[n];
				for (int a = 0;  a < n; ++a) {
					edges[a] = new LinkedList<Integer>();
					edgesR[a] = new LinkedList<Integer>();
				}
				for (int a = 0; a < n * n; ++a) {
					if (D[a] < all.get(i) || D[a] > all.get(j)) continue;
					int from = a / n;
					int to = a % n;
					edges[from].add(to);
					edgesR[to].add(from);
				}
				if (!allReach(n, edges) || !allReach(n, edgesR)) {
					++j;
				} else {
					break;
				}
			}
			if (j < all.size()) {
				ret = Math.min(ret, all.get(j) - all.get(i));
			} else {
				break;
			}
		}
		return ret;
	}

	private boolean allReach(int n, LinkedList<Integer>[] edges) {
		boolean[] seen = new boolean[n];
		LinkedList<Integer> q = new LinkedList<Integer>();
		q.add(0);
		seen[0] = true;
		int count = 1;
		while (!q.isEmpty()) {
			int cur = q.removeFirst();
			for (int v : edges[cur]) {
				if (!seen[v]) {
					seen[v] = true;
					q.add(v);
					++count;
				}
			}
		}
		return count == n;
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("HardProof (250 Points)");
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

            int[] D = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < D.length; ++i)
                D[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(D, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1467113488;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] D, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		HardProof instance = new HardProof();
		int __result = 0;
		try {
			__result = instance.minimumCost(D);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 692/HardProof.sample";
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
