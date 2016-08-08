using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

public class DivisibleSetDiv1 {
	public string isPossible(int[] b) {
        Array.Sort(b);
        Array.Reverse(b);
        int[] a = new int[b.Length];
        for (int i = 0; i < a.Length; ++i) {
            a[i] = i + 1;
        }
        for (int i = 0; i < 100000; ++i) {
            bool flag = true;
            for (int j = 0; j < b.Length; ++j) {
                int sum = 0;
                int need = a[j] * b[j];
                for (int k = 0; k < b.Length; ++k) {
                    if (j == k) continue;
                    sum += a[k];
                }
                if (need < sum) {
                    for (int k = j; k < b.Length; ++k) {
                        a[k]++;
                        flag = false;
                    }
                    break;
                }
            }
            if (flag) {
                return "Possible";
            }
        }
		return "Impossible";
	}

// CUT begin
	static bool DoTest(int[] b, string __expected) {
		DateTime startTime = DateTime.Now;
		Exception exception = null;
		DivisibleSetDiv1 instance = new DivisibleSetDiv1();
		string __result = "";
		try {
			__result = instance.isPossible(b);
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

		Console.Error.WriteLine("DivisibleSetDiv1 (300 Points)");
		Console.Error.WriteLine();

    	int nCases = 0, nPassed = 0;
    	using (var reader = File.OpenText("DivisibleSetDiv1.sample")) {
            while (true) {
                string line = reader.ReadLine();
                if (line == null || !line.StartsWith("--"))
                    break;

                int[] b = new int[int.Parse(reader.ReadLine())];
                for (int i = 0; i < b.Length; ++i)
                    b[i] = (int) Convert.ChangeType(reader.ReadLine(), typeof(int));
                reader.ReadLine();
                string __answer = (string) Convert.ChangeType(reader.ReadLine(), typeof(string));

                nCases++;
                if (cases.Count > 0 && !cases.Contains(nCases - 1))
                	continue;
                Console.Error.Write(string.Format("  Testcase #{0} ... ", nCases - 1));
                if (DoTest(b, __answer))
                    nPassed++;
            }
    	}

        if (cases.Count > 0) nCases = cases.Count;
		Console.Error.WriteLine();
		Console.Error.WriteLine(string.Format("Passed : {0}/{1} cases", nPassed, nCases));

		DateTime Jan1st1970 = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
		int T = (int)((DateTime.UtcNow - Jan1st1970).TotalSeconds - 1470593751);
		double PT = T / 60.0, TT = 75.0;
		Console.Error.WriteLine(string.Format("Time   : {0} minutes {1} secs", T / 60, T % 60));
		Console.Error.WriteLine(string.Format("Score  : {0:0.00} points", 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}
// CUT end
}
