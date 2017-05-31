import java.io.*;
import java.util.*;

public class ImageCompression {
	public String isPossible(String[] image, int k) {
        int n = image.length;
        int m = image[0].length();
        boolean can = true;
        for (int i = 0; i < n; i+=k) {
            for (int j = 0; j < m; j+=k) {
                for (int x = i; x < i + k; x++) {
                    for (int y = j; y < j + k; y++) {
                        if (image[x].charAt(y) != image[i].charAt(j)) {
                            can = false;
                        }
                    }
                }
            }
        }
		return can? "Possible":"Impossible";
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ImageCompression (250 Points)");
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

            String[] image = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < image.length; ++i)
                image[i] = Reader.nextLine();
            int k = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(image, k, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1496192424;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] image, int k, String __expected) {
		for (int i = 0; i < image.length; i++) {
			image[i] = new String(image[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ImageCompression instance = new ImageCompression();
		String __result = "";
		try {
			__result = instance.isPossible(image, k);
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
        private static final String dataFileName = "ImageCompression.sample";
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
