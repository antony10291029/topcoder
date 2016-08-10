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
#define REP(i,n) for(int i=0; i < n; ++i)
const int mod = 1e9 + 7;
int a[200010];
int cnt[35];
class XorOrderDiv1 {
    public:
    int get(int m, int n, int a0, int b) {
        for (int i = 0; i < n; ++i) {
            a[i] = (a0 + 1ll * i * b) & ((1<<m) - 1);
        }
        sort(a, a + n);
        int ans = 0;
        REP(i,n){
            REP(j, m) {
                int l = (a[i] & ~((1 <<j) - 1) ) ^ 1 << j;
                int r = l + (1 << j);
                cnt[j] = lower_bound(a, a + n, r) - lower_bound(a, a + n, l);
            }
            long long sum = 0;
            REP(j, m) REP(k, m) sum = (sum + 1ll * cnt[j] * cnt[k] % mod * (1ll << (m - 1 - (j != k))) % mod) % mod;
            ans ^= sum;
        }

        return ans;
    }
};

// CUT begin
ifstream data("XorOrderDiv1.sample");

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

bool do_test(int m, int n, int a0, int b, int __expected) {
    time_t startClock = clock();
    XorOrderDiv1 *instance = new XorOrderDiv1();
    int __result = instance->get(m, n, a0, b);
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
        int m;
        from_stream(m);
        int n;
        from_stream(n);
        int a0;
        from_stream(a0);
        int b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, n, a0, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1470833595;
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
        cout << "XorOrderDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
