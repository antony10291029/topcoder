import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.TreeSet;

public class FleetFunding {
	public int maxShips(int m, int[] k, int[] a, int[] b) {
		Factory[] factories = new Factory[k.length];
		int total = 0;
		for (int i = 0; i < k.length; ++i) {
			factories[i] = new Factory(i, a[i], b[i], k[i]);
			total += k[i];
		}
		Arrays.sort(factories, new Comparator<Factory>() {
			@Override
			public int compare(Factory o1, Factory o2) {
				return o1.a - o2.a;
			}
		});
		int left = 0;
		int right = total / m + 1;
		outer:
		while (right - left > 1) {
			int need = (left + right) / 2;
			int ptr = 0;
			TreeSet<Factory> available = new TreeSet<Factory>(new Comparator<Factory>() {
				@Override
				public int compare(Factory o1, Factory o2) {
					if (o1.b != o2.b) return o1.b - o2.b;
					return o1.id - o2.id;
				}
			});

			int at = 1;
			while (at <= m) {
				while (ptr < factories.length && factories[ptr].a <= at) {
					Factory nxt = factories[ptr];
					nxt.remains = nxt.k;
					available.add(nxt);
					++ptr;
				}
				while (!available.isEmpty() && available.first().b < at) {
					available.pollFirst();
				}
				int upto = m;
				if (ptr < factories.length) upto = Math.min(upto, factories[ptr].a - 1);
				if (!available.isEmpty()) upto = Math.min(upto, available.first().b);
				int required = (upto - at + 1) * need;
				while (required > 0) {
					if (available.isEmpty()) {
						right = need;
						continue outer;
					}
					Factory first = available.first();
					int by = Math.min(required, first.remains);
					first.remains -= by;
					required -= by;
					if (first.remains == 0) {
						available.pollFirst();
					}
				}
				at = upto + 1;
			}
			left = need;
		}
		return left;
	}
	static class Factory {
		int id;
		int a;
		int b;
		int k;
		int remains;
		public Factory(int id, int a, int b, int k) {
			this.id = id;
			this.a = a;
			this.b = b;
			this.k = k;
		}
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("FleetFunding (300 Points)");
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

            int m = Integer.parseInt(Reader.nextLine());
            int[] k = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < k.length; ++i)
                k[i] = Integer.parseInt(Reader.nextLine());
            int[] a = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < a.length; ++i)
                a[i] = Integer.parseInt(Reader.nextLine());
            int[] b = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < b.length; ++i)
                b[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(m, k, a, b, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1471513595;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int m, int[] k, int[] a, int[] b, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		FleetFunding instance = new FleetFunding();
		int __result = 0;
		try {
			__result = instance.maxShips(m, k, a, b);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 681/FleetFunding.sample";
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
