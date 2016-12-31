import java.io.*;
import java.util.*;
import java.math.*;

public class FindingKids {
    final int MOD = 1000000007;
	public long getSum(int n, int q, int A, int B, int C) {
        Set<Integer> locs = new HashSet<Integer>();
        long curr = A;
        State[] list = new State[n];
        for (int i = 0; i < n; ++i) {
            curr *= B;
            curr += C;
            curr %= MOD;
            int p = (int) curr;
            p %= (MOD - n + i + 1);
            if (!locs.add(p)) {
                p = MOD - n + i;
            }
            locs.add(p);
            list[i] = new State(i, p, p % 2 != 0);
        }
        int[] order = new int[n];
        Arrays.sort(list);
        ArrayList<Integer> inc = new ArrayList<Integer>();
        ArrayList<Integer> dec = new ArrayList<Integer>();
        for (int i = 0; i < order.length; ++i) {
            order[list[i].kidIndex] = i;
            if (list[i].l) {
                dec.add(list[i].x);
            } else {
                inc.add(list[i].x);
            }
        }
        long ret = 0;
        int[] kid = new int[q];
        int[] time = new int[q];
        for (int i = 0; i < q; ++i) {
            curr *= B;
            curr += C;
            curr %= MOD;
            kid[i] = (int) (curr%n);
            curr *= B;
            curr += C;
            curr %= MOD;
            time[i] = (int) curr;
        }
        for (int i = 0; i < q; ++i) {
            ret = Math.abs(solve(inc, dec, order[kid[i]] + 1, time[i]));

        }
        return ret;

	}

    public static long solve(ArrayList<Integer> inc, ArrayList<Integer> dec, int indexWant, int time) {
        int l = 0;
        int r = inc.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            long goal = inc.get(m) + time;
            int other1 = howManyLess(dec, - 1, goal, time);
            int other2 = howManyLessEq(dec, -1, goal, time);
            if (m + other1 <= indexWant - 1 && m + other2 >= indexWant - 1) {
                return goal;
            }
            else if (m + other1 >= indexWant) {
                r = m - 1;
            }
            else {
                l = m + 1;
            }

        }
        l = 0;
        r = dec.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            long goal = dec.get(m) - time;
            int other1 = howManyLess(inc, 1, goal, time);
            int other2 = howManyLessEq(inc, 1, goal, time);
            if (m + other1 <= indexWant - 1 && m + other2 >= indexWant - 1) {
                return goal;
            }
            else if (m + other1 >= indexWant) {
                return m - 1;
            }
            else {
                l = m + 1;
            }
        }
        throw new RuntimeException();
    }


    public static int howManyLess(ArrayList<Integer> list, int scale, long goal, int time) {
        if (list.isEmpty()) return 0;
        if (list.get(0) + scale * time >= goal) return 0;
        int l = 0;
        int r = list.size() - 1;
        while (l != r) {
            int m = (l + r + 1) / 2;
            if (list.get(m) + scale * time >= goal) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        return l + 1;

    }

    public static int howManyLessEq(ArrayList<Integer> list, int scale, long goal, int time) {
        if (list.isEmpty()) return 0;
        if (list.get(0) + scale * time > goal) return 0;
        int l = 0;
        int r = list.size() - 1;
        while (l != r) {
            int m = (l + r + 1) / 2;
            if (list.get(m) + scale * time > goal) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        return l + 1;
    }

    static class State implements Comparable<State> {
        public int kidIndex;
        public int x;
        public boolean l;
        public State(int kidIndex, int x, boolean l) {
            super();
            this.kidIndex = kidIndex;
            this.x = x;
            this.l = l;
        }
        public int compareTo(State s) {
            return x - s.x;
        }
    }

// CUT begin
	public static void main(String[] args){
		System.err.println("FindingKids (500 Points)");
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
            int q = Integer.parseInt(Reader.nextLine());
            int A = Integer.parseInt(Reader.nextLine());
            int B = Integer.parseInt(Reader.nextLine());
            int C = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, q, A, B, C, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1483168588;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, int q, int A, int B, int C, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		FindingKids instance = new FindingKids();
		long __result = 0;
		try {
			__result = instance.getSum(n, q, A, B, C);
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
        private static final String dataFileName = "FindingKids.sample";
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
