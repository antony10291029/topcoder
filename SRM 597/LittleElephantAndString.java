import java.io.*;
import java.util.*;

public class LittleElephantAndString {
	public int getNumber(String A, String B) {
        if (A.length() != B.length()) return -1;
        int[] c = new int[26];
        for (int i = 0; i < A.length(); ++i) {
            c[A.charAt(i) - 'A']++;
            c[B.charAt(i) - 'A']--;
        }
        for (int i = 0; i < 26; ++i) if (c[i] != 0) return -1;
        int ans = A.length();
        for (int i = A.length() - 1, j = B.length() - 1; i >= 0; --i) {
            if (A.charAt(i) == B.charAt(j)) {
                --ans;
                --j;
            }
        }
		return ans;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("LittleElephantAndString (250 Points)");
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

            String A = Reader.nextLine();
            String B = Reader.nextLine();
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(A, B, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1498700794;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String A, String B, int __expected) {
        A = new String(A);
        B = new String(B);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		LittleElephantAndString instance = new LittleElephantAndString();
		int __result = 0;
		try {
			__result = instance.getNumber(A, B);
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
        private static final String dataFileName = "LittleElephantAndString.sample";
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
