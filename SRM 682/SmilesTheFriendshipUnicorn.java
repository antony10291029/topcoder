import java.io.*;
import java.util.*;

public class SmilesTheFriendshipUnicorn {
	private List<Integer>[] adj;
	public String hasFriendshipChain(int N, int[] A, int[] B) {
		adj = new ArrayList[N];
		for (int i = 0; i < N; ++i) {
			adj[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < A.length; ++i) {
			int u = A[i], v = B[i];
			adj[u].add(v);
			adj[v].add(u);
		}
		for (int a = 0; a < N; ++a)
			for (int b : adj[a])
				if (a != b)
					for (int c : adj[b])
						if (c != b && c != a)
							for (int d : adj[c])
								if (d != a && d != b && d != c)
									for (int e : adj[d])
										if(e != a && e != b && e != c && e != d)
											return "Yay!";
		return ":(";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("SmilesTheFriendshipUnicorn (300 Points)");
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

            int N = Integer.parseInt(Reader.nextLine());
            int[] A = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < A.length; ++i)
                A[i] = Integer.parseInt(Reader.nextLine());
            int[] B = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < B.length; ++i)
                B[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, A, B, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1469720308;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int[] A, int[] B, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		SmilesTheFriendshipUnicorn instance = new SmilesTheFriendshipUnicorn();
		String __result = "";
		try {
			__result = instance.hasFriendshipChain(N, A, B);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 682/SmilesTheFriendshipUnicorn.sample";
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
