import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class AllGraphCuts {
	public int[] findGraph(int[] x) {
		int n = 1;
		while (n * n < x.length) ++n;
		int[][] a = new int[n][n];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[i][j] = x[i * n + j];
			}
		}
		ArrayList<Edge> res = solve(a);
		if (res == null) {
			return new int[]{-1};
		}
		int[] r = new int[res.size()];
		for (int i = 0; i < res.size(); ++i) {
			r[i] = res.get(i).x * n + res.get(i).y + res.get(i).w * n * n;
		}
		return r;
	}
	ArrayList<Edge> solve(int[][] g) {
		int n = g.length;
		if (n == 1) {
			if (g[0][0] != 0) {
				return null;
			}
			return new ArrayList<Edge>();
		}
		int mv = Integer.MAX_VALUE;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					mv = Math.min(mv, g[i][j]);
				}
			}
		}
		DisjointSets dsu = new DisjointSets(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] > mv) {
					dsu.unite(i, j);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dsu.root(i) == dsu.root(j)) {
					continue;
				}
				if (g[i][j] > mv) {
					return null;
				}
			}
		}
		ArrayList<Edge> res = new ArrayList<Edge>();
		int prevNode = -1;
		for (int i = 0; i < n; ++i) {
			if (dsu.root(i) != i) continue;
			ArrayList<Integer> comp = new ArrayList<Integer>();
			for (int j = 0; j < n; ++j) {
				if (dsu.root(j) == i) {
					comp.add(j);
				}
			}
			if (comp.size() == n) {
				return null;
			}
			ArrayList<Edge> part = solve(subsample(g, comp));
			if (part == null) {
				return null;
			}
			for (Edge e : part) {
				e.x = comp.get(e.x);
				e.y = comp.get(e.y);
				res.add(e);
			}
			if (prevNode != -1) {
				res.add(new Edge(prevNode, comp.get(0), mv));
			}
			prevNode = comp.get(0);
		}
		return res;
	}
	private int[][] subsample(int[][] g, ArrayList<Integer> inds) {
		int[][] res = new int[inds.size()][inds.size()];
		for (int i = 0; i < inds.size(); ++i) {
			for (int j = 0; j < inds.size(); ++j) {
				res[i][j] = g[inds.get(i)][inds.get(j)];
			}
		}
		return res;
	}
	static class Edge {
		int x;
		int y;
		int w;

		public Edge(int x, int y, int w) {
			this.x = x;
			this.y = y;
			this.w = w;
		}
	}

	class DisjointSets {
		int[] p;
		int[] rank;

		public DisjointSets(int size) {
			p = new int[size];
			for (int i = 0; i < size; ++i) {
				p[i] = i;
			}
			rank = new int[size];
		}
		public int root(int x) {
			while (x != p[x]) {
				x = p[x];
			}
			return x;
		}
		public void unite(int a, int b) {
			a = root(a);
			b = root(b);
			if (a == b) {
				return;
			}
			if (rank[a] < rank[b]) {
				p[a] = b;
			} else {
				p[b] = a;
				if (rank[a] == rank[b]) {
					++rank[a];
				}
			}
		}
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("AllGraphCuts (500 Points)");
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
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(x, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466065945;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] x, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		AllGraphCuts instance = new AllGraphCuts();
		int[] __result = new int[0];
		try {
			__result = instance.findGraph(x);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 687/AllGraphCuts.sample";
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
