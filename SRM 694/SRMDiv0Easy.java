import java.io.*;
import java.util.*;

public class SRMDiv0Easy {
	private static int curGen = 0;
	private static final int INF = (int) 1e9;

	SRMDiv0Easy.Edge addEdge(SRMDiv0Easy.Vertex a, SRMDiv0Easy.Vertex b, int cap) {
		SRMDiv0Easy.Edge ab = new SRMDiv0Easy.Edge();
		SRMDiv0Easy.Edge ba = new SRMDiv0Easy.Edge();
		ab.dest = b; ab.cap = cap; ab.flow = 0; ab.rev = ba;
		ba.dest = a; ba.cap = 0; ba.flow = 0; ba.rev = ab;
		a.outgo.add(ab);
		a.outgo.add(ba);
		return ab;
	}

	public int get(int N, int[] L, int[] R, int[] X, int[] Y) {
		SRMDiv0Easy.Vertex[] vs = new SRMDiv0Easy.Vertex[N + 1];
		for (int i = 0; i <= N; ++i) {
			vs[i] = new SRMDiv0Easy.Vertex();
		}
		int[] delta = new int[N + 1];
		SRMDiv0Easy.Edge[] direct = new SRMDiv0Easy.Edge[L.length];
		for (int i = 0; i < L.length; ++i) {
			direct[i] = addEdge(vs[L[i]], vs[R[i] + 1], Y[i] - X[i]);
			delta[L[i]] -= X[i];
			delta[R[i] + 1] += X[i];
		}
		SRMDiv0Easy.Edge loop = addEdge(vs[N], vs[0], INF);
		SRMDiv0Easy.Vertex s = new SRMDiv0Easy.Vertex();
		SRMDiv0Easy.Vertex t = new SRMDiv0Easy.Vertex();
		int need = 0;
		SRMDiv0Easy.Edge[] aux = new SRMDiv0Easy.Edge[N + 1];
		for (int i = 0; i <= N; ++i) {
			if (delta[i] < 0) {
				aux[i] = addEdge(vs[i], t, -delta[i]);
			} else {
				aux[i] = addEdge(s, vs[i], delta[i]);
			}
			need += Math.abs(delta[i]);
		}
		if (maxFlow(s, t) != need / 2) {
			return -1;
		}
		int res = loop.flow;
		loop.cap = loop.rev.cap = 0;
		loop.flow = loop.rev.flow = 0;
		for (SRMDiv0Easy.Edge e : aux) {
			e.cap = e.rev.cap = 0;
			e.flow = e.rev.flow = 0;
		}
		for (int i = 0; i < L.length; ++i) {
			direct[i].cap += X[i];
			direct[i].flow += X[i];
			direct[i].rev.cap -= X[i];
			direct[i].rev.cap -= X[i];
		}
		res += maxFlow(vs[0], vs[N]);
		return res;
	}

	private int maxFlow(SRMDiv0Easy.Vertex s, SRMDiv0Easy.Vertex t) {
		int res = 0;
		while(true) {
			++curGen;
			int by = s.dfs(t, INF);
			if (by == 0) break;
			res += by;
		}
		return res;
	}

	static class Edge {
		SRMDiv0Easy.Vertex dest;
		int cap;
		int flow;
		SRMDiv0Easy.Edge rev;
	}

	static class Vertex {
		int gen = 0;
		List<SRMDiv0Easy.Edge> outgo = new ArrayList<Edge>(1);
		int ptr = 0;
		public int dfs(SRMDiv0Easy.Vertex t, int max) {
			if (this == t) return max;
			if (gen == curGen) return 0;
			gen = curGen;
			for (int i = 0; i < outgo.size(); ++i) {
				SRMDiv0Easy.Edge e = outgo.get(ptr);
				if (e.flow < e.cap) {
					int nby = e.dest.dfs(t, Math.min(max, e.cap - e.flow));
					if (nby != 0) {
						e.flow += nby;
						e.rev.flow -= nby;
						return nby;
					}
				}
				++ptr;
				if (ptr >= outgo.size()) ptr = 0;
			}
			return 0;
		}
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("SRMDiv0Easy (900 Points)");
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
            int[] L = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < L.length; ++i)
                L[i] = Integer.parseInt(Reader.nextLine());
            int[] R = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < R.length; ++i)
                R[i] = Integer.parseInt(Reader.nextLine());
            int[] X = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < X.length; ++i)
                X[i] = Integer.parseInt(Reader.nextLine());
            int[] Y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < Y.length; ++i)
                Y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, L, R, X, Y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1468768717;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int[] L, int[] R, int[] X, int[] Y, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		SRMDiv0Easy instance = new SRMDiv0Easy();
		int __result = 0;
		try {
			__result = instance.get(N, L, R, X, Y);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 694/SRMDiv0Easy.sample";
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
