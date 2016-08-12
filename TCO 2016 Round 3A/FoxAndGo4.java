import java.io.*;
import java.util.*;

public class FoxAndGo4 {
	List<FoxAndGo4.Node> canonicals;
	public int score(int[] p) {
		int n = p.length + 1;
		FoxAndGo4.Node[] nodes = new FoxAndGo4.Node[n];
		for (int i = 0; i < n; ++i) {
			nodes[i] = new FoxAndGo4.Node();
		}
		for (int i = 0; i < p.length; ++i) {
			nodes[p[i]].children.add(nodes[i + 1]);
		}
		FoxAndGo4.Node root = nodes[0];
		root.initSubtreeSizes();
		FoxAndGo4.Node[] bySubtreeSize = nodes.clone();
		Arrays.sort(bySubtreeSize, new Comparator<FoxAndGo4.Node>() {

			@Override
			public int compare(Node o1, Node o2) {
				return o1.subtreeSize - o2.subtreeSize;
			}
		});
		Comparator<FoxAndGo4.Node> byIsomorphicId = new Comparator<FoxAndGo4.Node>() {
			@Override
			public int compare(Node o1, Node o2) {
				return o1.isomorphicId - o2.isomorphicId;
			}
		};
		Comparator<FoxAndGo4.Node> byChildren = new Comparator<FoxAndGo4.Node>() {
			@Override
			public int compare(Node o1, Node o2) {
				if (o1.children.size() != o2.children.size()) return o1.children.size() - o2.children.size();
				for (int i = 0; i < o2.children.size(); ++i) {
					if (o1.children.get(i).isomorphicId != o2.children.get(i).isomorphicId) {
						return o1.children.get(i).isomorphicId - o2.children.get(i).isomorphicId;
					}
				}
				return 0;
			}
		};
		int nextIsomorphicId = 0;
		canonicals = new ArrayList<FoxAndGo4.Node>();
		for (int i = 0; i < bySubtreeSize.length; ) {
			int j = i;
			while (j < bySubtreeSize.length && bySubtreeSize[i].subtreeSize == bySubtreeSize[j].subtreeSize) ++j;
			for (int k = i; k < j; ++k) {
				Collections.sort(nodes[k].children, byIsomorphicId);
			}
			Arrays.sort(bySubtreeSize, i, j, byChildren);
			FoxAndGo4.Node canonical = null;
			for (int k = i; k < j; ++k) {
				if (k == i || byChildren.compare(bySubtreeSize[k - 1], bySubtreeSize[k]) < 0) {
					++nextIsomorphicId;
					canonical = bySubtreeSize[k];
					canonicals.add(canonical);
				}
				bySubtreeSize[k].isomorphicId = nextIsomorphicId - 1;
				bySubtreeSize[k].ismorphicCanonical = canonical;
				++canonical.maxCount;
			}
			i = j;
		}
		if (root.ismorphicCanonical != root) throw new RuntimeException();
		--root.maxCount;
		long prod = 1;
		for (FoxAndGo4.Node c : canonicals) {
			c.cacheBase = prod;
			prod *= c.maxCount + 1;
		}
		long cacheKey = 0;
		for (FoxAndGo4.Node node : root.children) {
			++node.ismorphicCanonical.count;
			cacheKey += node.ismorphicCanonical.cacheBase;
		}
		Map<Long, Integer> cache = new HashMap<Long, Integer>();
		return rec(0, cacheKey, cache);
	}
	private int rec(int who, long cacheKey, Map<Long, Integer> cache) {
		Integer cached = cache.get(cacheKey * 2 + who);
		if (cached != null) {
			return cached;
		}
		int best;
		if (who == 0) {
			best = Integer.MAX_VALUE;
			for (FoxAndGo4.Node c : canonicals) {
				if (c.count > 0) {
					long newKey = cacheKey;
					--c.count;
					newKey -= c.cacheBase;
					for (FoxAndGo4.Node n : c.children) {
						++n.ismorphicCanonical.count;
						newKey += n.ismorphicCanonical.cacheBase;
					}
					best = Math.min(best, rec(1 - who, newKey, cache));
					++c.count;
					for (FoxAndGo4.Node n : c.children) {
						--n.ismorphicCanonical.count;
					}
				}
			}
			if (best == Integer.MAX_VALUE) best = 0;
		} else {
			best = 0;
			for (FoxAndGo4.Node c : canonicals) {
				if (c.count > 0) {
					long newKey = cacheKey;
					--c.count;
					newKey -= c.cacheBase;
					best = Math.max(best, c.subtreeSize - 1 + rec(1 - who, newKey, cache));
					++c.count;
				}
			}
		}
		cache.put(cacheKey * 2 + who, best);
		return best;
	}
	static class Node {
		int subtreeSize;
		int isomorphicId;
		FoxAndGo4.Node ismorphicCanonical;
		long cacheBase;
		int count;
		int maxCount;
		List<FoxAndGo4.Node> children = new ArrayList<Node>(1);
		public void initSubtreeSizes() {
			subtreeSize = 1;
			for (FoxAndGo4.Node node : children) {
				node.initSubtreeSizes();
				subtreeSize += node.subtreeSize;
			}
		}
	}
// CUT begin
	public static void main(String[] args){
		System.err.println("FoxAndGo4 (500 Points)");
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

            int[] p = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < p.length; ++i)
                p[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(p, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1470923872;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] p, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		FoxAndGo4 instance = new FoxAndGo4();
		int __result = 0;
		try {
			__result = instance.score(p);
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
        private static final String dataFileName = "/Users/resry/topcoder/TCO 2016 Round 3A/FoxAndGo4.sample";
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
