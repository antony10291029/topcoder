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
#define REP(i,a) for(int i = 0; i < (a); ++i)
typedef long long LL;
class PeriodicJumping {
    public:
    int minimalTime(int x, vector<int> jumpLengths) {
        if (x == 0) return 0;
        x = abs(x);
        vector<LL> a;
        LL n = jumpLengths.size();
        REP(i,n) a.push_back(jumpLengths[i]);
        LL sum = 0;
        REP(i,n) sum += a[i];
        if (sum > x) {
            LL mx = 0, cur = 0, idx = 0, res = 0;
            REP(i, 2 * n) {
                mx = max(mx, a[idx % n]);
                cur += a[idx % n];
                ++idx;
                ++res;
                if (cur >= x && mx - (cur - mx)  <= x) {
                    break;
                }
            }
            return res;
        }
        LL res = x / sum * n, idx = 0;
        sum = res * sum;
        while (sum < x) {
            sum += a[idx % n];
            ++idx;
            ++res;
        }
        return res;
    }
};

// CUT begin
ifstream data("PeriodicJumping.sample");

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

bool do_test(int x, vector<int> jumpLengths, int __expected) {
    time_t startClock = clock();
    PeriodicJumping *instance = new PeriodicJumping();
    int __result = instance->minimalTime(x, jumpLengths);
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
        int x;
        from_stream(x);
        vector<int> jumpLengths;
        from_stream(jumpLengths);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, jumpLengths, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502934376;
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
        cout << "PeriodicJumping (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
