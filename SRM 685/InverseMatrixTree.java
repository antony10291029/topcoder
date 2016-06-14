import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class InverseMatrixTree {

	final int mod = (int) 1e9 + 7;

    int det(int[][] a) {
		int n = a.length;
		int det = 1;
		for (int i = 0; i < n; ++i) {
			int k = i;
			for (int j = i + 1; j < n; ++j) {
				if (a[j][i] > a[k][i]) {
					k = j;
				}
			}
			if (a[k][i] == 0) {
				det = 0;
				break;
			}
			int[] tmp = a[i];a[i] = a[k];a[k] = tmp;
			if (i != k) {
				det = -det;
			}
			det = (int) ((det * 1L * a[i][i]) % mod);
			int inv = BigInteger.valueOf(a[i][i])
					.modInverse(BigInteger.valueOf(mod)).intValue();
			for (int j = i + 1; j < n; ++j) {
				a[i][j] = (int) ((a[i][j] * 1L * inv) % mod);

			}
			for (int j = 0; j < n; ++j) {
				if (j != i & a[j][i] != 0) {
					for (int k1 = i + 1; k1 < n; ++k1) {
						a[j][k1] = (int) ((a[j][k1] - a[i][k1] * 1L * a[j][i]) % mod);
						if (a[j][k1] < 0) {
							a[j][k1] += mod;
						}
					}
				}
			}
		}
		return det;
	}

    int cnt(boolean[][] g) {
        int n = g.length;
        int[][] a = new int[n][n];
        for (int i = 0; i < n; ++i) {
            int sz = 0;
            for (int j = 0; j < n; ++j) {
                sz += g[i][j] ? 1 : 0;
                a[i][j] = g[i][j] ? -1 : 0;
            }
            a[i][i] = sz;
        }
        int[][] b = new int[n - 1][n - 1];
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                b[i][j] = a[i][j];
            }
        }
        int res = det(b);
        if (res < 0) {
            res += mod;
        }
        return res;
    }

    class Road {
        int fr, to;

        public Road(int fr, int to) {
            super();
            this.fr = fr;
            this.to = to;
        }

        @Override
        public String toString() {
            return "fr=" + fr + ", to =" + to + "\n";
        }
    }

	ArrayList<Road> gen(boolean[][] g) {
		ArrayList<Road> res = new ArrayList<Road>();
		for (int i = 0; i < g.length; i++) {
			for (int j = i + 1; j < g.length; j++) {
				if (g[i][j]) {
					res.add(new Road(i, j));
				}
			}
		}
		return res;
	}
	ArrayList<Road> combine(ArrayList<Road> r1, int n1, ArrayList<Road> r2) {
		ArrayList<Road> res = new ArrayList<Road>();
		for (Road r : r1) {
			res.add(r);
		}
		for (Road r: r2) {
			res.add(new Road(r.fr + n1, r.to + n1));
		}
		if (n1 != 0) {
			res.add(new Road(0, n1));
		}
		return res;
	}
	int[] genAnswer(ArrayList<Road> g, int n) {
		int[] res = new int[g.size() + 1];
		res[0] = n;
		int it = 1;
		for (Road r: g) {
			res[it++] = r.fr * n + r.to;
		}
		return res;
	}

	public int[] constructGraph(int r) {
		final int MAX = 10;
		Random rnd = new Random(123);
		final int TO = 1000;
		ArrayList<Road>[] can = new ArrayList[TO];
		int[] canSz = new int[TO];
		for (int it = 0; it < 123123; ++it) {
			int n = 1 + rnd.nextInt(MAX);
			boolean[][] g = new boolean[n][n];
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < i; ++j) {
					if (rnd.nextBoolean()) {
						g[i][j] = g[j][i] = true;
					}
				}
			}
			int c = cnt(g);
			if (c < TO && can[c] == null) {
				can[c] = gen(g);
				canSz[c] = n;
			}
		}
		if (r == 0) {
			return genAnswer(can[0], canSz[0]);
		}
		if (r == 1) {
			return genAnswer(can[1], canSz[1]);
		}
		long need = r + rnd.nextInt(100) * 1L * mod;
		// long need = r;
		while (true) {
			long cur = need;
			ArrayList<Integer> add = new ArrayList<Integer>();
			for (int i = TO - 1; i > 1; --i) {
				while (can[i] != null && cur % i == 0) {
					cur /= i;
					add.add(i);
				}
			}
			if (cur == 1) {
				int curN = 0;
				ArrayList<Road> curG = new ArrayList<Road>();
				for (int now : add) {
					int nextN = curN + canSz[now];
					curG = combine(curG, curN, can[now]);
					curN = nextN;
				}
				return genAnswer(curG, curN);
			}
			need += mod;
		}

	}

// CUT begin
	public static void main(String[] args){
		System.err.println("InverseMatrixTree (1000 Points)");
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

            int r = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int[] __answer = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(r, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466993920;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int r, int[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		InverseMatrixTree instance = new InverseMatrixTree();
		int[] __result = new int[0];
		try {
			__result = instance.constructGraph(r);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 685/InverseMatrixTree.sample";
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
