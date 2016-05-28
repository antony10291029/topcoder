import java.io.*;
import java.util.*;

public class DivFree {
  static final int P = 1000000007;
  static class Sign {
    List<Integer> a;
    public Sign(List<Integer> a) {
      this.a = a;
    }
    @Override
    public int hashCode() {
      final int prime = 31;
      int result = 1;
      result = prime * result + ((a == null) ? 0:a.hashCode());
      return result;
    }
    @Override
    public boolean equals(Object obj) {
      if (this == obj)
        return true;
      if (obj == null)
        return false;
      if (getClass() != obj.getClass())
        return false;
      Sign other = (Sign) obj;
      if (a == null) {
        if (other.a != null) {
          return false;
        }
      } else if (!a.equals(other.a)) {
        return false;
      }
      return true;
    }
  }
  private int[][] mul(int[][] a, int[][] b) {
    int n = a.length;
    int[][] c = new int[n][n];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          c[i][j] += (int) ((long)a[i][k] * b[k][j] % P);
          c[i][j] %= P;
        }
      }
    }
    return c;
  } 
  private int[][] pow(int[][] a, int b) {
    int n = a.length;
    int[][] ret = new int[n][n];
    //I
    for (int i = 0; i < n; ++i) {
      ret[i][i] = 1;
    }
    for (; b > 0; b >>= 1) {
      if ((b&1) == 1) {
        ret = mul(ret, a);
      }
      a = mul(a, a);
    }
    return ret;
  }
	public int dfcount(int n, int k) {
    HashMap<Sign, Integer> map = new HashMap<Sign, Integer>();
    List<Integer> id2Number = new ArrayList<Integer>();
    int[] arr = new int[k + 1];

    for (int i = 1; i <= k; ++i) {
      int ii = i;
      List<Integer> cur = new ArrayList<Integer>();
      for (int j = 2; j * j <= ii; ++j) {
        int p = 0;
        while (ii % j == 0) {
          ii /= j;
          p++;
        }
        if (p != 0) {
          cur.add(p);
        }
      }
      if (ii != 1) {
        cur.add(1);
      }
      Collections.sort(cur);
      Sign curSign = new Sign(cur);
      if (!map.containsKey(curSign)) {
        map.put(curSign, map.size());
        id2Number.add(i);
      }
      arr[i] = map.get(curSign);
    }
    int m = map.size();

    int[] cnt = new int[m];
    for (int i = 1; i <= k; ++i) {
      cnt[arr[i]]++;
    }

    int[][] a = new int[m][m];

    for (int i = 0; i < m; ++i) {
      int x = id2Number.get(i);

      a[i] = cnt.clone();
      if (x == 1) {
        continue;
      }
      for (int j = 1; j * j <= x; ++j) {
        if (x % j == 0) {
          a[i][arr[j]]--;
          if (j * j != x && j != 1) {
            a[i][arr[x/j]]--;
          }
        }
      }
    }




    a = pow(a, n-1);
    //System.out.println(Arrays.toString(cnt));
    //System.out.println(Arrays.deepToString(a));


    int ret = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        ret += (int)((long) cnt[i] * a[i][j] % P);
        ret %= P;
      }
    }
    return ret;

	}

// CUT begin
	public static void main(String[] args){
		System.err.println("DivFree (600 Points)");
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
            int k = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(n, k, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1459665460;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, int k, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		DivFree instance = new DivFree();
		int __result = 0;
		try {
			__result = instance.dfcount(n, k);
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
        private static final String dataFileName = "DivFree.sample";
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
