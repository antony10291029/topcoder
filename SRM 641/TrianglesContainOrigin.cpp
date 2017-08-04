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
const double PI = 4 * atan(1);
typedef long long LL;
#define SIZE(x) x.size()
#define REP(x,a) for(int i=0;i<(a);++i)

class TrianglesContainOrigin {
    public:
    int find(int l, int r, double d, vector<double> ang) {
        ++r;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (ang[m] < d) l = m;
            else r = m;
        }
        return l;
    }
    long long count(vector<int> x, vector<int> y) {
        vector<double> ang;
        int n = SIZE(x);
        REP(i,n) {
            double angle = atan2(y[i], x[i]);// angle: [-PI,PI]
            ang.push_back(angle);
            ang.push_back(angle + 2 * PI);
        }
        sort(ang.begin(), ang.end());
        LL res = 1LL * n * (n - 1) * (n - 2) / 6;//calc C(n,3)
        REP(i,n) {
            int l = i, r = i + n;
            double d = ang[i] + PI;
            int idx = find(l, r, d, ang);
            int cnt = idx - i;
            res -= 1LL * cnt * (cnt - 1) / 2; // calc C(cnt, 2)
        }
        return res;
    }
};

// CUT begin
ifstream data("TrianglesContainOrigin.sample");

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

bool do_test(vector<int> x, vector<int> y, long long __expected) {
    time_t startClock = clock();
    TrianglesContainOrigin *instance = new TrianglesContainOrigin();
    long long __result = instance->count(x, y);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501721400;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TrianglesContainOrigin (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
