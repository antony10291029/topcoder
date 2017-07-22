import java.io.*;
import java.util.*;

public class DengklekGaneshAndTree {
    private Vertex[] vs;
    private boolean[] was;
    private Segment dfs(int u) {
        was[u] = true;
        Segment s = new Segment(vs[u].h);
        for (int v : vs[u].edges) {
            if (vs[v].ch == vs[u].ch) {
                s.update(dfs(v));
            }
        }
        return s;
    }
	public int getCount(String labels, int[] parents) {
        int n = labels.length();
        vs = new Vertex[n];
        for (int i = 0; i < n; ++i) {
            vs[i] = new Vertex(labels.charAt(i));
        }
        int high = 0;
        for (int i = 1; i < n; ++i) {
            int pa = parents[i - 1];
            vs[pa].edges.add(i);
            vs[i].h = vs[pa].h + 1;
            high = Math.max(high, vs[i].h);
        }
        ++high;
        was = new boolean[n];
        List<Segment> a = new ArrayList<Segment>();
        for (int i = 0; i < n; ++i) {
            if (!was[i]) {
                a.add(dfs(i));
            }
        }
        Collections.sort(a);
        int[] dp = new int[n+1];
        int[] cur = new int[n+1];
        dp[0] = 1;
        for (Segment s : a) {
            for (int i = 0; i < n+1; ++i) cur[i] = dp[i];
            for (int i = s.a; i <= high; ++i) {
                int nxt = Math.max(i, s.b);
                cur[nxt] = (cur[nxt] + dp[i]) % 1000000007;
            }
            for (int i = 0; i < n+1; ++i) dp[i] = cur[i];
        }

		return dp[high];
	}
    private static class Vertex {
        public int h;
        public char ch;
        public List<Integer> edges = new ArrayList<Integer>();
        public Vertex(){}
        public Vertex(char ch) {
            this.ch = ch;
            this.h = 0;
        }
    }
    private static class Segment implements Comparable {
        public int a;
        public int b;
        public Segment(int a) {
            this.a = a;
            this.b = a + 1;
        }
        public void update(Segment s) {
            a = Math.min(a, s.a);
            b = Math.max(b, s.b);
        }
        public int compareTo(Object o) {
            Segment s = (Segment) o;
            return this.a - s.a;
        }
    }

// CUT begin
	public static void main(String[] args){
		System.err.println("DengklekGaneshAndTree (500 Points)");
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

            String labels = Reader.nextLine();
            int[] parents = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < parents.length; ++i)
                parents[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(labels, parents, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1500710869;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String labels, int[] parents, int __expected) {
        labels = new String(labels);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		DengklekGaneshAndTree instance = new DengklekGaneshAndTree();
		int __result = 0;
		try {
			__result = instance.getCount(labels, parents);
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
        private static final String dataFileName = "DengklekGaneshAndTree.sample";
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
