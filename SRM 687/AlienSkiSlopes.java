import java.io.*;
import java.util.*;

class MinCostFlow {
	static final long INF = Long.MAX_VALUE;
	public List<Edge>[] graph;
	public long[] pot;
	public void init(int n) {
		graph = new ArrayList[n];
		for (int i = 0; i < n; ++i) {
			graph[i] = new ArrayList<Edge>();
		}
	}

	public Edge addEdge(int s, int t, int cap, int cost) {
		Edge edge =new Edge(s, t, graph[t].size(), cap, cost);
		graph[s].add(edge);
		Edge rev  = new Edge(t, s, graph[s].size() - 1, 0, -cost);
		graph[t].add(rev);
		return edge;
	}

	static Path getPath(Edge[] p, int s, int t) {
		Path path = new Path();
		path.f = Integer.MAX_VALUE;
		for (; t != s; t = p[t].u) {
			path.edges.add(p[t]);
			path.f = Math.min(path.f, p[t].cap - p[t].f);
		}
		return path;
	}

	static boolean bellmanFord(List<Edge>[] graph, int s, long[] dist) {
		Arrays.fill(dist, INF);
		dist[s] = 0;
		int n = graph.length;
		boolean updated = false;
		for (int step = 0; step < n; ++step) {
			updated = false;
			for (int u = 0; u < n; ++u) {
				if (dist[u] < INF) {
					for (Edge e : graph[u]) {
						if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
							dist[e.v] = Math.max(dist[u] + e.cost, -INF);
							updated = true;
						}
					}
				}
			}
			if (!updated) {
				break;
			}
		}
		return updated == false;
	}
	public long[] minCostFlow(int s, int t) {
		pot = new long[graph.length];
		if (!bellmanFord(graph, s, pot)) {
			throw new IllegalArgumentException("Negative cycles are not suppported");
		}
		int flow = 0;
		long flowCost = 0;
		while (true) {
			Queue<QItem> q = new PriorityQueue<QItem>();
			q.add(new QItem(0, s));
			Edge[] p = new Edge[graph.length];
			long[] prio = new long[graph.length];
			Arrays.fill(prio, INF);
			prio[s] = 0;
			while (!q.isEmpty()) {
				QItem cur = q.poll();
				if (cur.prio != prio[cur.v]) {
					continue;
				}
				if (cur.v == t && prio[cur.v] == 0) {
					break;
				}
				for (Edge e : graph[cur.v]) {
					long nprio = prio[cur.v] + e.cost + pot[cur.v] - pot[e.v];
					if (e.cap > e.f && prio[e.v] > nprio) {
						prio[e.v] = nprio;
						p[e.v] = e;
						q.add(new QItem(nprio, e.v));
					}
				}
			}
			if (p[t] == null) {
				break;
			}
			for (int i = 0; i < graph.length; ++i) {
				if (p[i] != null) {
					pot[i] += prio[i];
				}
			}
			Path path = getPath(p, s, t);
			for (Edge e : path.edges) {
				e.f += path.f;
				graph[e.v].get(e.rev).f -= path.f;
				flowCost += ((long)path.f) * e.cost;

			}
			flow += path.f;
		}
		return new long[]{flow, flowCost};
	}



	public static class Edge {
		public int u;
		public int v;
		public int rev;
		public int cap;
		public int f;
		public long cost;

		public Edge(int u, int v, int rev, int cap, long cost) {
			this.u = u;
			this.v = v;
			this.rev = rev;
			this.cap = cap;
			this.cost = cost;
		}
	}

	static class Path {
		public List<Edge> edges = new ArrayList<Edge>();
		public int f;
	}

	static class QItem implements Comparator<QItem> , Comparable<QItem>{

		long prio;
		int v;
		public QItem(long prio, int v) {
			this.prio = prio;
			this.v = v;
		}

		@Override
		public int compare(QItem o1, QItem o2) {
			return o1.prio < o2.prio ? -1 : o1.prio > o2.prio ? 1 : 0;
		}

		@Override
        public int compareTo(QItem o) {
            return prio < o.prio ? -1 : prio > o.prio ? 1 : 0;
		}
	}
}

public class AlienSkiSlopes {
	public int[] raise(int[] h) {
		int n = 1;
		while (n * n < h.length) ++n;
		int S = 2 * n, T = 2 * n + 1;
		MinCostFlow g = new MinCostFlow();
		g.init(T + 1);
		MinCostFlow.Edge[][] middle = new MinCostFlow.Edge[n][n];
		for (int i = 0; i < n; ++i) {
			g.addEdge(S, i, 1, 0);
			g.addEdge(i + n, T, 1, 0);
			for (int j = 0; j < n; ++j) {
				middle[i][j] = g.addEdge(i, j + n, 1, -h[i * n + j]);
			}
		}
		long[] flow = g.minCostFlow(S, T);
		int[] res = new int[n];
		for (int i = 0; i < n; ++i) {
			res[i] = (int) g.pot[i + n];
		}
		int mv = 0;
		for (int i = 0; i < n; ++i) {
			mv = Math.max(mv, res[i]);
		}
		for (int i = 0; i < n; ++i) {
			res[i] = mv - res[i];
		}
		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("AlienSkiSlopes (1000 Points)");
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

            int[] h = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < h.length; ++i)
                h[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(h, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466154137;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] h, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		AlienSkiSlopes instance = new AlienSkiSlopes();
		int[] __result = new int[0];
		try {
			__result = instance.raise(h);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 687/AlienSkiSlopes.sample";
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
