#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
int dp[110][110][110], C[310][310], num[310];
const int mo = (int) (1e9 + 7);
int pow(int a, int b) {
    int n = 1;
    while (b) {
        if (b & 1) n = 1ll * n * a % mo;
        a = 1ll * a * a % mo;
        b >>= 1;
    }
    return n;
}
class RandomWalkOnGrid {
    public:
    int getExpectation(int x0, int y0, int t, int n, int m) {
        for (int i = 0; i <= 100; ++i) {
            C[i][0] = 1;
            for (int  j = 1; j <= i; ++j) {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mo;
            }
        }
        x0 = (x0 + mo) % mo;
        y0 = (y0 + mo) % mo;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = 1; k <= i + j; ++k) {
                    for (int k1 = 0; k1 < i; ++k1) 
                        if ((i - k1) % 2 == 0) dp[i][j][k] = (dp[i][j][k] + 2ll * dp[k1][j][k - 1] % mo * C[i][k1]) % mo;
                    for (int k1 = 0; k1 < j; ++k1) 
                        if ((j - k1) % 2 == 0) dp[i][j][k] = (dp[i][j][k] + 2ll * dp[i][k1][k - 1] % mo * C[j][k1]) % mo;
                }
            }
        }
        int ans = 0;
        num[0] = 1;
        for (int i = 1; i <= max(n, m); ++i) num[i] = 1ll * num[i - 1] * (t - i + 1) % mo * pow(i, mo - 2) % mo;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = 0; k <= i + j && k <= t; ++k) {
                    ans = (ans + 1ll * dp[i][j][k] * num[k] % mo * C[n][i] % mo * C[m][j] % mo * pow(x0, n - i) % mo * pow(y0, m - j) % mo * pow(4, t - k)) % mo;
                }
            }
        }
        ans = (ans + mo) % mo;

        return ans;
    }
};

// CUT begin
ifstream data("RandomWalkOnGrid.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int x0, int y0, int t, int n, int m, int __expected) {
    time_t startClock = clock();
    RandomWalkOnGrid *instance = new RandomWalkOnGrid();
    int __result = instance->getExpectation(x0, y0, t, n, m);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int x0;
        from_stream(x0);
        int y0;
        from_stream(y0);
        int t;
        from_stream(t);
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x0, y0, t, n, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469664879;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "RandomWalkOnGrid (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
