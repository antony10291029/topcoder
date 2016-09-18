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
const int md = 1e9 + 7;
const int N = 1000042;
int fact[N], inv[N];
int pw(int a, int b) {
    int x = 1, step = 1 << 30;
    while (step > 0) {
        x = (long long) x * x % md;
        if (step & b) x = (long long) x * a % md;
        step >>= 1;
    }
    return x;
}
int C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    int x = fact[n];
    int y = inv[k];
    int z = inv[n - k];
    return (long long) x * y % md * z % md;
}
class LittleElephantAndBoard {
    public:
    int getNumber(int M, int R, int G, int B) {
        fact[0] = 1;
        for (int i = 1; i < N; ++i) fact[i] = (long long)fact[i - 1] * i % md;
        inv[0] = 1;
        for (int i = 1; i < N; ++i) inv[i] = pw(fact[i], md - 2);
        if (R > M || G > M || B > M) {
            return 0;
        }
        int rb = M - G, rg = M - B, bg = M - R;
        int ans = 0;
        for (int cnt_rb = 0; cnt_rb <= rb; ++cnt_rb) {
            if (rb > 0 && cnt_rb == 0) continue;
            for (int cnt_rg = cnt_rb - 1; cnt_rg <= cnt_rb + 1 && cnt_rg <= rg; ++cnt_rg) {
                if (cnt_rg < 0) continue;
                if(rg > 0 && cnt_rg == 0) continue;
                int need = (rb - cnt_rb) + (rg - cnt_rg);
                if (need > bg) continue;
                int have = rg + rb + 1;
                if (bg > have) continue;
                int cur = 2;
                if (cnt_rg == cnt_rb) cur *= 2;
                if (rb > 0) cur = (long long) cur * C(rb - 1, cnt_rb - 1) % md;
                if (rg > 0) cur = (long long) cur * C(rg - 1, cnt_rg - 1) % md;
                cur = (long long) cur * C(have - need, bg - need) % md;
                ans = (ans + cur) % md;
            }
        }
        return ans;

    }
};

// CUT begin
ifstream data("LittleElephantAndBoard.sample");

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

bool do_test(int M, int R, int G, int B, int __expected) {
    time_t startClock = clock();
    LittleElephantAndBoard *instance = new LittleElephantAndBoard();
    int __result = instance->getNumber(M, R, G, B);
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
        int M;
        from_stream(M);
        int R;
        from_stream(R);
        int G;
        from_stream(G);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(M, R, G, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474246928;
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
        cout << "LittleElephantAndBoard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
