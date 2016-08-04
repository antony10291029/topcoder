using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

public class EllysAndor {
	public string canGet(int[] numbers, int goal) {
        var g = N(goal);
        for (var i = numbers.Length - 1; i >= 0; --i) {
            var n = N(numbers[i]);
            var o = O(g, n);
            var a = A(g, n);
            if (C(g, o)) {
                OR(g, n);
            } else if (C(g, a)) {
                AND(g, n);
            }
            if (G(g)) {
                return "Possible";
            }
        }
		return "Impossible";
	}
    int [] O(int[] a, int[] b) {
        var r = new int[31];
        for (var i = 0; i < 31; ++i) {
            r[i] = a[i] == 2 || b[i] == 2 ? 2 : (a[i] == 1 || b[i] == 1 ? 1 : 0);
        }
        return r;
    }
    bool G(int[] g) {
        for (var i = 0; i < 31; ++i) {
            if (g[i] == 1)  {
                return false;
            }
        }
        return true;
    }
    bool C(int[] a, int[] b) {
        for (var i = 0; i < 31; ++i) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
    int[] A(int[] a, int[] b) {
        var r = new int[31];
        for (var i = 0; i < 31; ++i) {
            r[i] = a[i] == 2 || b[i] == 2 ? 2 : (a[i] == 0 || b[i] == 0 ? 0 : 1);
        }
        return r;
    }
    void AND(int[] g, int[] n) {
        for (var i = 0; i < 31; ++i) {
            if (n[i] == 0) {
                g[i] = 2;
            }
        }
    }
    void OR(int[] g, int[] n) {
        for (var i = 0; i < 31; ++i) {
            if (n[i] == 1) {
                g[i] = 2;
            }
        }
    }
    int[] N(int n) {
        var r = new int[31];
        for (var i = 0; i < 31; ++i) {
            r[i] = (n >> i) & 1;
        }
        return r;
    }

// CUT begin
	static bool DoTest(int[] numbers, int goal, string __expected) {
		DateTime startTime = DateTime.Now;
		Exception exception = null;
		EllysAndor instance = new EllysAndor();
		string __result = "";
		try {
			__result = instance.canGet(numbers, goal);
		}
		catch (Exception e) { exception = e; }
		TimeSpan __elapsed = new TimeSpan(DateTime.Now.Ticks - startTime.Ticks);

		if (exception != null) {
			Console.Error.WriteLine("RUNTIME ERROR!");
			Console.Error.WriteLine(exception);
			return false;
		}
		else if (__result == __expected) {
			Console.Error.WriteLine("PASSED! " + string.Format("({0:0.00} seconds)", __elapsed.TotalSeconds));
			return true;
		}
		else {
			Console.Error.WriteLine("FAILED! " + string.Format("({0:0.00} seconds)", __elapsed.TotalSeconds));
			Console.Error.WriteLine("           Expected: " + "\"" + __expected + "\"");
			Console.Error.WriteLine("           Received: " + "\"" + __result + "\"");
			return false;
		}
	}

	public static void Main(string[] args){
		HashSet<int> cases = new HashSet<int>();
        for (int i = 0; i < args.Length; ++i) cases.Add(int.Parse(args[i]));

		Console.Error.WriteLine("EllysAndor (1000 Points)");
		Console.Error.WriteLine();

    	int nCases = 0, nPassed = 0;
    	using (var reader = File.OpenText("EllysAndor.sample")) {
            while (true) {
                string line = reader.ReadLine();
                if (line == null || !line.StartsWith("--"))
                    break;

                int[] numbers = new int[int.Parse(reader.ReadLine())];
                for (int i = 0; i < numbers.Length; ++i)
                    numbers[i] = (int) Convert.ChangeType(reader.ReadLine(), typeof(int));
                int goal = (int) Convert.ChangeType(reader.ReadLine(), typeof(int));
                reader.ReadLine();
                string __answer = (string) Convert.ChangeType(reader.ReadLine(), typeof(string));

                nCases++;
                if (cases.Count > 0 && !cases.Contains(nCases - 1))
                	continue;
                Console.Error.Write(string.Format("  Testcase #{0} ... ", nCases - 1));
                if (DoTest(numbers, goal, __answer))
                    nPassed++;
            }
    	}

        if (cases.Count > 0) nCases = cases.Count;
		Console.Error.WriteLine();
		Console.Error.WriteLine(string.Format("Passed : {0}/{1} cases", nPassed, nCases));

		DateTime Jan1st1970 = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
		int T = (int)((DateTime.UtcNow - Jan1st1970).TotalSeconds - 1470236919);
		double PT = T / 60.0, TT = 75.0;
		Console.Error.WriteLine(string.Format("Time   : {0} minutes {1} secs", T / 60, T % 60));
		Console.Error.WriteLine(string.Format("Score  : {0:0.00} points", 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}
// CUT end
}
