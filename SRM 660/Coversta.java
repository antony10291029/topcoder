import java.io.*;
import java.util.*;

public class Coversta {
    boolean in(int x, int y ,int r, int c) {
        return x >= 0 && x < r && y >= 0 && y < c;
    }
	public int place(String[] a, int[] x, int[] y) {
        int r = a.length;
        int c = a[0].length();
        int[][] f = new int[r][c];
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                for (int k = 0; k < x.length; ++k) {
                    int nx = i + x[k];
                    int ny = j + y[k];
                    if (in(nx, ny, r, c)) {
                        f[i][j] += a[nx].charAt(ny) - '0';
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int s1 = f[i][j];
                for (int k = 0; k < x.length; ++k) {
                    int nx = i + x[k];
                    int ny = j + y[k];
                    if (in(nx, ny, r, c)) {
                        for (int k2 = 0; k2 < x.length; ++k2) {
                            int nx2 = nx - x[k2];
                            int ny2 = ny - y[k2];
                            if (in(nx2, ny2, r, c)) {
                                f[nx2][ny2] -= a[nx].charAt(ny) - '0';
                            }
                        }
                    }
                }
                for (int nx = 0; nx < r; ++nx) {
                    for (int ny = 0; ny < c; ++ny) {
                        res = Math.max(res, s1 + f[nx][ny]);
                    }
                }
                for (int k = 0; k < x.length; ++k) {
                    int nx = i + x[k];
                    int ny = j + y[k];
                    if (in(nx, ny, r, c)) {
                        for (int k2 = 0; k2 < x.length; ++k2) {
                            int nx2 = nx - x[k2];
                            int ny2 = ny - y[k2];
                            if (in(nx2, ny2, r, c)) {
                                f[nx2][ny2] += a[nx].charAt(ny) - '0';
                            }
                        }
                    }
                }
            }
        }


		return res;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("Coversta (250 Points)");
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

            String[] a = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < a.length; ++i)
                a[i] = Reader.nextLine();
            int[] x = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < x.length; ++i)
                x[i] = Integer.parseInt(Reader.nextLine());
            int[] y = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < y.length; ++i)
                y[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(a, x, y, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1498390531;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] a, int[] x, int[] y, int __expected) {
		for (int i = 0; i < a.length; i++) {
			a[i] = new String(a[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		Coversta instance = new Coversta();
		int __result = 0;
		try {
			__result = instance.place(a, x, y);
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
        private static final String dataFileName = "Coversta.sample";
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
