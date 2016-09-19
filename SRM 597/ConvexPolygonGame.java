import java.io.*;
import java.util.*;

public class ConvexPolygonGame {
	static class SingleLineChecker {
		int cnt;
		int x1;
		int y1;
		int x2;
		int y2;
		long a;
		long b;
		long c;


		boolean handle(int x, int y) {
			if (cnt == 0) {
				cnt = 1;
				x1 = x;
				y1 = y;
				return true;
			} else if (cnt == 1) {
				cnt = 2;
				x2 = x;
				y2 = y;
				a = y2 - y1;
				b = x1 - x2;
				c = -(a * x1 + b * y1);
				return true;
			} else {
				return a * x + b * y + c == 0;
			}
		}
	}
	public String winner(int[] X, int[] Y) {
		int min = 0;
		int max = 0;
		for (int i = 0; i < X.length; ++i)
			if (X[i] < X[min] || X[i] == X[min] && Y[i] < Y[min]) min = i;
		for (int i = 0; i < X.length; ++i)
			if (X[i] > X[max] || X[i] == X[max] && Y[i] > Y[max]) max = i;
		int n = X.length;
		int bottomStart = min;
//		int bottomEnd = max;
//		if (X[(max + n - 1) % n] == X[max]) bottomEnd = (max + n - 1) % n;
//		int topEnd = max;
		int topStart = min;
		if (X[(min + n - 1) % n] == X[min]) topStart = (min + n - 1) % n;
		SingleLineChecker checker = new SingleLineChecker();
		for (int x = X[min]; x <= X[max]; ++x) {
			while (X[(bottomStart + 1) % n] < x) bottomStart = (bottomStart + 1) % n;
			while (X[(topStart + n - 1) % n] < x) topStart = (topStart + n - 1) % n;
			int bottomx1 = X[bottomStart];
			int bottomy1 = Y[bottomStart];
			int bottomNext = (bottomStart + 1) % n;
			int bottomx2 = X[bottomNext];
			int bottomy2 = Y[bottomNext];
			long bottomp = (x - bottomx1) * (long) bottomy2 + (bottomx2 - x) * (long) bottomy1;
			long bottomq = bottomx2 - bottomx1;
			if (bottomq <= 0) throw new RuntimeException();
			long bottomcoord = bottomp / bottomq - 1;
			while (bottomcoord * bottomq < bottomp) ++bottomcoord;
			if (x == bottomx1 || x == bottomx2) ++bottomcoord;
			int topx1 = X[topStart];
			int topy1 = Y[topStart];
			int topNext = (topStart + n - 1) % n;
			int topx2 = X[topNext];
			int topy2 = Y[topNext];
			long topp = (x - topx1) * (long) topy2 + (topx2 - x) * (long) topy1;
			long topq = topx2 - topx1;
			if (topq <= 0) throw new RuntimeException();
			long topcoord = topp / topq + 1;
			while (topcoord * topq > topp) --topcoord;
			if (x == topx1 || x == topx2) --topcoord;
			if (bottomcoord <= topcoord) {
				for (long y = bottomcoord; y <= topcoord; ++y)
					if (!checker.handle(x, (int) y)) return "Masha";
			}
		}
		return "Petya";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ConvexPolygonGame (600 Points)");
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

            int[] X = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < X.length; ++i)
                X[i] = Integer.parseInt(Reader.nextLine());
            int[] Y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < Y.length; ++i)
                Y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(X, Y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1474244971;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] X, int[] Y, String __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ConvexPolygonGame instance = new ConvexPolygonGame();
		String __result = "";
		try {
			__result = instance.winner(X, Y);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 597/ConvexPolygonGame.sample";
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
