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
#define SZ(x) x.size()

string x, y;

const int MX = 55;
const int MOD = 1e9 + 7;
int dp[MX][MX][2*MX];

void add(int &x, int y) {
    x = (x + y) % MOD;
}

int f(int a,int b, int sum) {
    if (a >= SZ(x) && b >= SZ(y)) {
        if (sum == 0) return 1;
        return 0;
    }
    if (dp[a][b][sum] != -1) return dp[a][b][sum];
    int s = 0;
    if (a < SZ(x)) {
        if (x[a] == '(') add(s, f(a + 1, b, sum + 1));
        else if (sum > 0) add(s, f(a + 1, b, sum - 1));
    }
    if (b < SZ(y)) {
        if (y[b] == '(') add(s, f(a, b + 1, sum + 1));
        else if (sum > 0) add(s, f(a, b + 1, sum - 1));
    }
    dp[a][b][sum] = s;
    return s;
}

class InterleavingParenthesisDiv2 {
    public:
    int countWays(string s1, string s2) {
        x = s1;
        y = s2;
        memset(dp, 0xff, sizeof(dp));
        return f(0, 0, 0);
    }
};

// CUT begin
ifstream data("InterleavingParenthesisDiv2.sample");

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

bool do_test(string s1, string s2, int __expected) {
    time_t startClock = clock();
    InterleavingParenthesisDiv2 *instance = new InterleavingParenthesisDiv2();
    int __result = instance->countWays(s1, s2);
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
        string s1;
        from_stream(s1);
        string s2;
        from_stream(s2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s1, s2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500103252;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "InterleavingParenthesisDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
