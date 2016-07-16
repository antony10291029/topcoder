import java.io.*;
import java.util.*;

public class TriangleFree {
	public long count(int n, int[] x, int[] y) {
		TriangleFree.Edge[][] edge = new TriangleFree.Edge[n][n];
		TriangleFree.Vertex[] vs = new TriangleFree.Vertex[n];
		for (int i = 0; i < n; ++i) {
			vs[i] = new TriangleFree.Vertex();
		}
		for (int i = 0; i < x.length; ++i) {
			TriangleFree.Edge e = new TriangleFree.Edge();
			e.a = vs[Math.min(x[i], y[i])];
			e.b = vs[Math.max(x[i], y[i])];
			edge[x[i]][y[i]] = e;
			edge[y[i]][x[i]] = e;
		}
		for (int a = 0; a < n; ++a) {
			for (int b = a + 1; b < n; ++b) {
				for (int c = b + 1; c < n; ++c){
					if (edge[a][b] != null && edge[b][c] != null && edge[a][c] != null) {
						TriangleFree.Triangle t = new TriangleFree.Triangle();
						t.vertices.add(vs[a]);
						t.vertices.add(vs[b]);
						t.vertices.add(vs[c]);
						edge[a][b].hasTriangles = true;
						edge[b][c].hasTriangles = true;
						edge[a][c].hasTriangles = true;
						vs[a].triangles.add(t);
						vs[b].triangles.add(t);
						vs[c].triangles.add(t);
					}
				}
			}
		}
		for (int a = 0; a < n; ++a) {
			for (int b = a + 1; b < n; ++b) {
				TriangleFree.Edge e = edge[a][b];
				if (e != null) {
					if (!e.hasTriangles) {
						edge[a][b] = edge[b][a] = null;
					} else {
						vs[a].edges.add(edge[a][b]);
						vs[b].edges.add(edge[b][a]);
					}
				}
			}
		}
		long res = 1;
		for (TriangleFree.Vertex v : vs) {
			if (!v.mark) {
				List<TriangleFree.Vertex> comp = new ArrayList<TriangleFree.Vertex>();
				v.dfs(comp);
				res *= doit(comp);
			}
		}
		return res;
	}
	private long doit(List<TriangleFree.Vertex> comp) {
		for (TriangleFree.Vertex v : comp) {
			v.cnts = v.triangles.size();
		}
		return rec(comp);
	}
	private long rec(List<TriangleFree.Vertex> comp) {
		TriangleFree.Vertex best = null;
		for (TriangleFree.Vertex v : comp) {
			if (best == null || v.cnts > best.cnts) {
				best = v;
			}
		}
		if (best == null) return 1;
		if (best.cnts == 0) {
			return 1L << comp.size();
		}
		comp.remove(best);
		boolean ok = true;
		for (TriangleFree.Triangle t : best.triangles) {
			if (t.cnt >= 0) {
				--t.cnt;
				if (0 == t.cnt) ok = false;
			}
		}
		long res = 0;
		if (ok) {
			for (TriangleFree.Triangle t : best.triangles) {
				if (t.cnt >= 0) {
					for (TriangleFree.Vertex v : t.vertices) {
						v.cnts -= 1L << (10 * (2 - t.cnt));
						v.cnts += 1L << (10 * (3 - t.cnt));
					}
				}
			}
			res += rec(comp);

			for (TriangleFree.Triangle t : best.triangles) {
				if (t.cnt >= 0) {
					for (TriangleFree.Vertex v : t.vertices) {
						v.cnts += 1L << (10 * (2 - t.cnt));
						v.cnts -= 1L << (10 * (3 - t.cnt));
					}
				}
			}
		}
		for (TriangleFree.Triangle t : best.triangles) {
			if (t.cnt >= 0) {
				++t.cnt;
			}
		}

		int curGen = comp.size() + 1;
		for (TriangleFree.Triangle t : best.triangles) {
			if (t.cnt >= 0) {
				for (TriangleFree.Vertex v : t.vertices) {
					v.cnts -= 1L << (10 * (3 - t.cnt));
				}
				t.cnt = -((curGen << 2) + t.cnt);
			}
		}
		res +=rec(comp);
		for (TriangleFree.Triangle t : best.triangles) {
			if ((t.cnt < 0) && (((-t.cnt) >> 2) == curGen)) {
				t.cnt = (-t.cnt) & 3;
				for (TriangleFree.Vertex v : t.vertices) {
					v.cnts += 1L << (10 * (3 - t.cnt));
				}
			}
		}
		comp.add(best);
		return res;
	}
	protected static class Triangle {
		int cnt = 3;
		List<TriangleFree.Vertex>vertices = new ArrayList<TriangleFree.Vertex>(3);
	}
	protected static class Edge {
		TriangleFree.Vertex a;
		TriangleFree.Vertex b;
		boolean hasTriangles;
	}
	protected static class Vertex implements Comparable<TriangleFree.Vertex> {

		boolean mark = false;
		int cnts;
		List<TriangleFree.Edge> edges = new ArrayList<TriangleFree.Edge>();
		List<TriangleFree.Triangle>triangles = new ArrayList<TriangleFree.Triangle>(1);
		public void dfs(List<TriangleFree.Vertex> comp) {
			if (mark) return;
			mark = true;
			comp.add(this);
			for (TriangleFree.Edge e : edges) {
				if (e.a == this) e.b.dfs(comp);
				else e.a.dfs(comp);
			}
		}
		@Override
		public int compareTo(Vertex o) {
			return cnts - o.cnts;
		}
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TriangleFree (1000 Points)");
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
            int[] x = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < x.length; ++i)
                x[i] = Integer.parseInt(Reader.nextLine());
            int[] y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < y.length; ++i)
                y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, x, y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1468632212;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, int[] x, int[] y, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TriangleFree instance = new TriangleFree();
		long __result = 0;
		try {
			__result = instance.count(n, x, y);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 693/TriangleFree.sample";
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
