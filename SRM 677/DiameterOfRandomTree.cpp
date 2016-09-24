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

#define SZ(x) ((int)(x.size()))
#define REP(i, a, b) for(int i = (a); i < (b); ++i)

const int maxn = 128;

int n, n2, d;
vector<int> g[maxn];
double f[maxn][maxn];
double h[maxn][maxn];

void mergeto(double f[], double t[]) {
    double g[maxn];
    memset(g, 0, sizeof(g));
    REP(i, 0, n2) REP(j, 0, n2) {
        if (i + j + 1 <= d) g[max(i, j + 1)] += f[i] * t[j] * 0.5;
        if (i + j + 2 <= d) g[max(i, j + 2)] += f[i] * t[j] * 0.5;
    }
    memcpy(f, g, sizeof(g));
}
void solve(int p, int prev) {
    REP(i, 0, SZ(g[p])) if (g[p][i] != prev) solve(g[p][i], p);
    memset(f[p], 0, sizeof(f[p]));
    f[p][0] = 1;
    REP(i, 0, SZ(g[p])) if (g[p][i] != prev) mergeto(f[p], f[g[p][i]]);

}
class DiameterOfRandomTree {
    public:
    double getExpectation(vector<int> a, vector<int> b) {
        n = SZ(a) + 1;
        REP(i, 0, n - 1) g[a[i]].push_back(b[i]);
        REP(i, 0, n - 1) g[b[i]].push_back(a[i]);
        double ret = 0;
        double prev = 0;
        n2 = n + n;
        REP(k, 1, n2) {
            d = k;
            solve(0, -1);
            double current = 0;
            REP(l, 0, n2) current += f[0][l];
            ret += k * (current - prev);
            prev = current;
        }
        return ret;
    }
};

// CUT begin
ifstream data("DiameterOfRandomTree.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> a, vector<int> b, double __expected) {
    time_t startClock = clock();
    DiameterOfRandomTree *instance = new DiameterOfRandomTree();
    double __result = instance->getExpectation(a, b);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474592631;
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
        cout << "DiameterOfRandomTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
