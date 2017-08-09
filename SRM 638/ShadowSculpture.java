import java.io.*;
import java.util.*;

public class ShadowSculpture {
    private int n;
    private String[] XY;
    private String[] YZ;
    private String[] ZX;
    private int[] dx = {1, 0, 0, 0, 0, -1}; 
    private int[] dy = {0, 1, 0, -1, 0, 0}; 
    private int[] dz = {0, 0, -1, 0, 1, 0}; 
    boolean check(int x, int y, int z) {
        if (x < 0 || x >= n) return false;
        if (y < 0 || y >= n) return false;
        if (z < 0 || z >= n) return false;
        if (XY[x].charAt(y) == 'N') return false;
        if (YZ[y].charAt(z) == 'N') return false;
        if (ZX[z].charAt(x) == 'N') return false;
        return true;

    }
	public String possible(String[] XY, String[] YZ, String[] ZX) {
        n = XY.length;
        this.XY = XY;
        this.YZ = YZ;
        this.ZX = ZX;
        boolean flag = false;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            if (XY[i].charAt(j) == 'Y') flag = true;
            if (YZ[i].charAt(j) == 'Y') flag = true;
            if (ZX[i].charAt(j) == 'Y') flag = true;
        }
        if (!flag) return "Possible";
        for (int x = 0; x < n; ++x) for (int y = 0; y < n; ++y) for (int z = 0; z < n; ++z) if (check(x, y, z)) {
            ArrayDeque<Integer>Q = new ArrayDeque<Integer>();
            Q.add(x);
            Q.add(y);
            Q.add(z);
            boolean[][][] used = new boolean[n][n][n];
            used[x][y][z] = true;
            while (Q.size() > 0) {
                int cx = Q.remove();
                int cy = Q.remove();
                int cz = Q.remove();
                for (int dir = 0; dir < 6; ++dir) {
                    int nx = cx + dx[dir];
                    int ny = cy + dy[dir];
                    int nz = cz + dz[dir];
                    if (check(nx, ny, nz) && !used[nx][ny][nz]) {
                        used[nx][ny][nz] = true;
                        Q.add(nx);
                        Q.add(ny);
                        Q.add(nz);
                    }
                }
            }
            boolean possible = true;
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
                if (XY[i].charAt(j) == 'Y') {
                    boolean ok = false;
                    for (int k = 0; k < n; ++k) if (used[i][j][k]) ok = true;
                    if (!ok) possible = false;
                }
                if (YZ[i].charAt(j) == 'Y') {
                    boolean ok = false;
                    for (int k = 0; k < n; ++k) if (used[k][i][j]) ok = true;
                    if (!ok) possible = false;
                }
                if (ZX[i].charAt(j) == 'Y') {
                    boolean ok = false;
                    for (int k = 0; k < n; ++k) if (used[j][k][i]) ok = true;
                    if (!ok) possible = false;
                }
            }
            if (possible) return "Possible";
        }
		return "Impossible";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ShadowSculpture (300 Points)");
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

            String[] XY = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < XY.length; ++i)
                XY[i] = Reader.nextLine();
            String[] YZ = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < YZ.length; ++i)
                YZ[i] = Reader.nextLine();
            String[] ZX = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < ZX.length; ++i)
                ZX[i] = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(XY, YZ, ZX, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1502066821;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] XY, String[] YZ, String[] ZX, String __expected) {
		for (int i = 0; i < XY.length; i++) {
			XY[i] = new String(XY[i]);
		}
		for (int i = 0; i < YZ.length; i++) {
			YZ[i] = new String(YZ[i]);
		}
		for (int i = 0; i < ZX.length; i++) {
			ZX[i] = new String(ZX[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ShadowSculpture instance = new ShadowSculpture();
		String __result = "";
		try {
			__result = instance.possible(XY, YZ, ZX);
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
        private static final String dataFileName = "ShadowSculpture.sample";
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
