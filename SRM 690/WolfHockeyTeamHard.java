import java.io.*;
import java.util.*;

public class WolfHockeyTeamHard {
	private long[] fact;
	private long[] invfact;
	private long[] inv;
	private static int mod = (int) (1e9 + 7);
	public long comb(int n, int k) {
		if (k > n || k < 0) return 0;
		return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
	}
	public int count(int N, int K) {
		if (K == 2 * N - 1) return 0;
		fact = new long[2 * N + 1];
		invfact = new long[2 * N + 1];
		inv = new long[2 * N + 1];
		inv[1] = 1;
		for (int i = 2; i < fact.length; ++i) {
			inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		}
		fact[0] = 1;
		invfact[0] = 1;
		for (int i = 1; i < fact.length; ++i) {
			fact[i] = fact[i - 1] * i % mod;
			invfact[i] = invfact[i - 1] * inv[i] % mod;
		}
		long ans = 0;
		for (int firstX = 2 * N - 2; firstX >= N - 1; --firstX) {
			int usedO = 2 * N - 1 - firstX;
			int sx = usedO + 1;
			int sy = usedO - 1;
			int gx = 2 * N;
			int gy = 0;
			int numdown = sy - gy;
			int numleft = 2 * N - 1 - numdown - usedO;
			numdown += numleft / 2;
			int numup = numleft / 2;
			long nways = comb(numup + numdown, numup) % mod;
			int numdown2 = sy - gy + 2;
			int numleft2 = 2 * N - 1 - numdown2 - usedO;
			int numup2 = numleft2 / 2;
			numdown2 += numleft2 / 2;
			long bad = comb(numup2 + numdown2, numup2) % mod;
			nways = (nways + mod - bad % mod) % mod;
			long nchoices = 2 * N - 1 - Math.max(K, firstX) - 1;
			ans = (ans + nways + nways * nchoices % mod) % mod;
		}
		ans = ans * 2 % mod;
		ans = ans * fact[N] % mod;
		return (int) ans;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("WolfHockeyTeamHard (900 Points)");
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

            int N = Integer.parseInt(Reader.nextLine());
            int K = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, K, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1466941726;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int K, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		WolfHockeyTeamHard instance = new WolfHockeyTeamHard();
		int __result = 0;
		try {
			__result = instance.count(N, K);
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
        private static final String dataFileName = "/Users/resry/topcoder/SRM 690/WolfHockeyTeamHard.sample";
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
