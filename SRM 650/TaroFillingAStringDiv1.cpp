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
typedef pair<int, int> PII;
typedef long long LL;
const int MOD = 1e9 + 7;
//const int MAXN = 1000000001;
//LL dp[MAXN][2];
vector<PII> s;
LL pow_mod(LL x, LL y) {
    LL t = 1;
    while (y > 0) {
        if (y & 1) t = (t * x) % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return t;
}
class TaroFillingAStringDiv1 {
    public:
    int getNumber(int N, vector<int> position, string value) {
        s.clear();
        int n = position.size();
        for (int i = 0; i < n; ++i) {
            s.push_back(PII(position[i], value[i] - 'A'));
        }
       // dp[1][0] = 1;
       // dp[1][1] = 2;
       // for (int i = 2; i < N; ++i) {
       //     if (i % 2 == 0) {
       //         dp[i][0] = (dp[i -1][0] + dp[i-1][1]) % MOD;
       //         dp[i][1] = 1;
       //     } else {
       //         dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
       //         dp[i][0] = 1;
       //     }
       // }
       // for (int i = 1; i < N; ++i) {
       //     cout << "i=" << i << " " << dp[i][0] << " " << dp[i][1] << endl;
       // }
        sort(s.begin(), s.end());
        LL res = 1;
        for (int i = 1; i < n; ++i) {
            int p1 = s[i-1].first;
            int p2 = s[i].first;
            int c1 = s[i-1].second;
            int c2 = s[i].second;
            int tmp = p2 - p1 - 1;
            if (tmp <= 0) {
                continue;
            }
            if (c1 == c2) {
                if (tmp % 2 == 0) res = (res * (tmp + 1)) % MOD;
            } else {
                if (tmp % 2 == 1) res = (res * (tmp + 1)) % MOD;
            }

        }
        return res;
    }
};

// CUT begin
ifstream data("TaroFillingAStringDiv1.sample");

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

bool do_test(int N, vector<int> position, string value, int __expected) {
    time_t startClock = clock();
    TaroFillingAStringDiv1 *instance = new TaroFillingAStringDiv1();
    int __result = instance->getNumber(N, position, value);
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
        int N;
        from_stream(N);
        vector<int> position;
        from_stream(position);
        string value;
        from_stream(value);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, position, value, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500860499;
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
        cout << "TaroFillingAStringDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
