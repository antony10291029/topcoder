using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
public class RepeatString
{
    public int minimalModify(string str)
    {
        var len = str.Length;
 
        Func<string, string, int> f = (s, t) =>
        {
            var n = s.Length;
            var m = t.Length;
            var dp = new int[n, m];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    dp[i, j] = -1;
            Func<int, int, int> dfs = null;
            dfs = (x, y) =>
            {
                if (x >= n)
                    return m - y;
                if (y >= m)
                    return n - x;
                if (dp[x, y] >= 0)
                    return dp[x, y];
                var ret = int.MaxValue;
                ret = Math.Min(ret, 1 + dfs(x + 1, y));
                ret = Math.Min(ret, 1 + dfs(x, y + 1));
                var ch = s[x] == t[y] ? 0 : 1;
                ret = Math.Min(ret, ch + dfs(x + 1, y + 1));
                return dp[x, y] = ret;
            };
            return dfs(0, 0);
        };
        var min = 1000000;
        for (int i = 0; i <= len; i++)
        {
            var u = str.Substring(0, i);
            var v = str.Substring(i);
            min = Math.Min(min, f(u, v));
 
        }
        return min;
    }
 
}