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
typedef long long ll;
ll solve(ll c, ll p) {
    ll ret = 0;
    for (; c > 0; p >>= 2) {
        ret += c / p;
        c %= p;
    }
    return ret;
}
ll solve(ll sa, ll sb, ll da, ll db) {
    if (sa > da || sb > db) return -1;
    ll ret = -1;
    for (ll cp = 0, p = 1; p * sa <= da && p * sb <= db; p *= 2, ++cp) {
        ll ca = da - p * sa;
        ll cb = db - p * sb;
        if (ca != cb) continue;
        ll t = solve(ca, p) + cp;
        if (ret < 0 || t < ret) ret = t;
    }
    return ret;
}
class DoubleOrOneEasy {
    public:
    int minimalSteps(int a, int b, int newA, int newB) {
        return solve(a, b, newA, newB);
    }
};

// CUT begin
ifstream data("DoubleOrOneEasy.sample");

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

bool do_test(int a, int b, int newA, int newB, int __expected) {
    time_t startClock = clock();
    DoubleOrOneEasy *instance = new DoubleOrOneEasy();
    int __result = instance->minimalSteps(a, b, newA, newB);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int newA;
        from_stream(newA);
        int newB;
        from_stream(newB);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, newA, newB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474505674;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DoubleOrOneEasy (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
