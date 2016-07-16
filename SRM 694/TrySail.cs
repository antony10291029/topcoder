using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

public class TrySail {
    public int get(int[] strength) {
        var dp = new bool[256, 256];
        dp[0, 0] = true;
        var all = 0;
        foreach (var x in strength) {
            var next = new bool[256, 256];
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    if (dp[i, j]) {
                        next[i ^ x, j] = true;
                        next[i, j ^ x] = true;
                        next[i, j] = true;
                    }
                }
            }
            dp = next;
            all ^= x;
        }
        var res = 0;
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 256; ++j) {
                if (dp[i, j]) {
                    res = Math.Max(res, i + j + (all ^ i ^ j));
                }
            }
        }
        return res;
    }

// CUT begin
	static bool DoTest(int[] strength, int __expected) {
		DateTime startTime = DateTime.Now;
		Exception exception = null;
		TrySail instance = new TrySail();
		int __result = 0;
		try {
			__result = instance.get(strength);
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
			Console.Error.WriteLine("           Expected: " + __expected);
			Console.Error.WriteLine("           Received: " + __result);
			return false;
		}
	}

	public static void Main(string[] args){
		HashSet<int> cases = new HashSet<int>();
        for (int i = 0; i < args.Length; ++i) cases.Add(int.Parse(args[i]));

		Console.Error.WriteLine("TrySail (250 Points)");
		Console.Error.WriteLine();

    	int nCases = 0, nPassed = 0;
    	using (var reader = File.OpenText("TrySail.sample")) {
            while (true) {
                string line = reader.ReadLine();
                if (line == null || !line.StartsWith("--"))
                    break;

                int[] strength = new int[int.Parse(reader.ReadLine())];
                for (int i = 0; i < strength.Length; ++i)
                    strength[i] = (int) Convert.ChangeType(reader.ReadLine(), typeof(int));
                reader.ReadLine();
                int __answer = (int) Convert.ChangeType(reader.ReadLine(), typeof(int));

                nCases++;
                if (cases.Count > 0 && !cases.Contains(nCases - 1))
                	continue;
                Console.Error.Write(string.Format("  Testcase #{0} ... ", nCases - 1));
                if (DoTest(strength, __answer))
                    nPassed++;
            }
    	}

        if (cases.Count > 0) nCases = cases.Count;
		Console.Error.WriteLine();
		Console.Error.WriteLine(string.Format("Passed : {0}/{1} cases", nPassed, nCases));

		DateTime Jan1st1970 = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
		int T = (int)((DateTime.UtcNow - Jan1st1970).TotalSeconds - 1468681816);
		double PT = T / 60.0, TT = 75.0;
		Console.Error.WriteLine(string.Format("Time   : {0} minutes {1} secs", T / 60, T % 60));
		Console.Error.WriteLine(string.Format("Score  : {0:0.00} points", 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}
// CUT end
}
