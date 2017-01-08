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

typedef long long ll;
using namespace std;
int f[2100],C[2100][2100],g[2100];
const int mod = 1000000007;
int quick(int k1, int k2) {
    int k3 = 1;
    while (k2) {
        if (k1 & 1) k3 = 1ll * k3 * k1 % mod;
        k1 = 1ll * k1 * k1 % mod;
        k2 >>= 1;
    }
}


class AlmostEulerianGraph {
    public:
    int calculateGraphs(int n) {
        int num = 1;
        for (int i = 0; i <= n; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
        for (int i = 1; i <= n; i++) f[i] = quick(2, (i - 1) * (i - 2) / 2);
        for (int i = 1; i <= n; i++) {
            g[i] = f[i];
            for (int j = 1; j < i; j++) g[i] = (g[i] - 1ll * g[j] * C[i - 1][j - 1] % mod * f[i - j]) % mod;
            g[i] = (g[i] + mod) % mod;
        }
        return 1ll * g[n] * (n * (n-1) / 2 + 1) % mod;
        return 0;
    }
};

// CUT begin
ifstream data("AlmostEulerianGraph.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    AlmostEulerianGraph *instance = new AlmostEulerianGraph();
    int __result = instance->calculateGraphs(n);
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
        int n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483491546;
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
        cout << "AlmostEulerianGraph (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
