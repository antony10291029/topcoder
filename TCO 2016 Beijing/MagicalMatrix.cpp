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
struct node {
    double q, e;
    node() {}
    node(double _q, double _e) : q(_q), e(_e) {}
    bool operator < (const node &t) const {
        return e * t.q < q * t.e;
    }
};
#define REP(i,a,b) for(int i=(a);i<(b);++i)
double p[15][255], dp[1<<10];
int pre[1<<10];
double q[255], s[255], f[255];

class MagicalMatrix {
    public:
    double MagicalInspection(int n, int m, vector<int> prob) {
        REP(i,0,n) REP(j,0,m) p[i][j] = (double) prob[i * m + j] / 100;
        REP(j,0,m) {
            q[j] = 1.0;
            REP(i,0,n) q[j] *= p[i][j];
            REP(i,0,1<<n) dp[i]= 15;
            dp[0] = 0;
            memset(pre, 0, sizeof pre);
            REP(mask, 0, 1<<n) REP(i,0,n) {
                if (mask & (1<<i)) continue;
                if (dp[mask | (1<<i)] > p[i][j] * dp[mask] + 1) {
                    dp[mask | (1<<i)] = p[i][j] * dp[mask] + 1;
                    pre[mask | (1<<i)] = i;
                }
            }
            s[j] = dp[(1<<n) - 1];
        }
        vector<node> v;
        v.clear();
        REP(i,0,m) v.push_back(node(q[i], s[i]));
        sort(v.begin(), v.end());
        double res = 0.0, tmp = 1.0;
        REP(i,0,m) {
            res += tmp * v[i].e;
            tmp *= (1 - v[i].q);
        }
        return res;
    }
};

// CUT begin
ifstream data("MagicalMatrix.sample");

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

bool do_test(int n, int m, vector<int> prob, double __expected) {
    time_t startClock = clock();
    MagicalMatrix *instance = new MagicalMatrix();
    double __result = instance->MagicalInspection(n, m, prob);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        vector<int> prob;
        from_stream(prob);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, prob, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1470011824;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MagicalMatrix (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
