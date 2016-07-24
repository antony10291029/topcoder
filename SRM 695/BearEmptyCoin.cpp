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
#define REP(i,n) for(i=0;i<n;++i)
typedef long long ll;
ll dp[66][66];
int can[66];
int gcd(int a, int b) {
        while (b > 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }


class BearEmptyCoin {
    public:
    long long winProbability(int K, int S) {
        if (S % K == 0) return 1LL << K;
        for (int r = 1; r <= K - 1; ++r) {
            can[r] = ((S % gcd(r, K)) == 0);
        }
        dp[0][0] = 1;
        for (int r = 1; r <= K - 1; ++r) {
            dp[r][0] = 1;
            for (int j = 1; j <= K - 1; ++j) {
                dp[r][j] = dp[r - 1][j - 1] + dp[r - 1][j];
            }
        }
        ll res = 0;
        for (int r = 1; r <= K - 1; ++r) {
            ll tmp = 0;
            for (int j = 1; j <= r; ++j) {
                if (can[j]) tmp = max(tmp, dp[r - 1][j - 1]);
            }
            res += tmp;
        }

        return res * 2;
    }
};

// CUT begin
ifstream data("BearEmptyCoin.sample");

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

bool do_test(int K, int S, long long __expected) {
    time_t startClock = clock();
    BearEmptyCoin *instance = new BearEmptyCoin();
    long long __result = instance->winProbability(K, S);
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
        int K;
        from_stream(K);
        int S;
        from_stream(S);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(K, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469320652;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 800 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BearEmptyCoin (800 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
