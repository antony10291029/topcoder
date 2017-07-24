import java.io.*;
import java.util.*;

public class RobotOnMoon {
    private static final int[] dx = new int[]{1, 0, -1, 0};
    private static final int[] dy = new int[]{0, -1, 0, 1};
    private int r, c;
    private int sx, sy;
    private String[] g;
    private boolean in(int x, int y) {
        return x >= 0 && x < r && y >= 0 && y < c;
    }
    private int check(int dir) {
        int curX = sx;
        int curY = sy;
        int len = 0;
        while (true) {
            int nX = curX + dx[dir];
            int nY = curY + dy[dir];
            if (!in(nX, nY)) {
                break;
            }
            if (g[nX].charAt(nY) == '#') {
                return -1;
            }
            ++len;
            curX = nX;
            curY = nY;
        }
        return len;
    }
	public int longestSafeCommand(String[] board) {
        r = board.length;
        c = board[0].length();
        g = board;
        for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) {
            if (g[i].charAt(j) == 'S') {
                sx = i;
                sy = j;
            }
        }
        int res[] = new int[2];
        for (int dir = 0; dir < 2; dir++) {
            int len1 = check(dir);
            int len2 = check(dir + 2);
            if (len1 == -1 || len2 == -1) {
                return -1;
            }
            res[dir] = Math.max(res[dir], len1 + len2);
        }
		return res[0] + res[1];
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("RobotOnMoon (250 Points)");
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

            String[] board = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < board.length; ++i)
                board[i] = Reader.nextLine();
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(board, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1500804128;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] board, int __expected) {
		for (int i = 0; i < board.length; i++) {
			board[i] = new String(board[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		RobotOnMoon instance = new RobotOnMoon();
		int __result = 0;
		try {
			__result = instance.longestSafeCommand(board);
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
        private static final String dataFileName = "RobotOnMoon.sample";
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
