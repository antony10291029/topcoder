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
typedef pair<int,int> PII;
#define FI first
#define SE second
#define SIZE(x) x.size()
#define REP(i,a) for(int i=0;i<(a);++i)
const int INF = 0x7f7f7f7f;
int dp[500][500];
vector<PII> a;
class JanuszTheBusinessman {
    public:
    bool inter(int i, int j) {
        int x1 = a[i].FI, x2 = a[j].FI;
        int y1 = a[i].SE, y2 = a[j].SE;
        return max(x1, x2) <= min(y1, y2);
    }
    int makeGuestsReturn(vector<int> arrivals, vector<int> departures) {
        int n = SIZE(arrivals);
        a.clear();
        for (int i = 0; i < n; ++i) a.push_back(PII(arrivals[i], departures[i]));
        sort(a.begin(), a.end());
        memset(dp, 0x7f, sizeof(dp));
        REP(i,n) {
            int j = 0;
            while (j < n && inter(j, i)) dp[j][i] = 1, j += 1;
        }
        REP(i,n) {
            REP(j,n) {
                if (dp[i][j] < INF) {
                    REP(k,n) {
                        int r = i + 1;
                        while (r < n && inter(r, k)) dp[r][k] = min(dp[r][k], dp[i][j] + 1), r += 1;
                    }
                }
            }
        }
        int res = INF;
        REP(i,n) {
            res = min(res, dp[n-1][i]);
        }
        return res;
    }
};

// CUT begin
ifstream data("JanuszTheBusinessman.sample");

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

bool do_test(vector<int> arrivals, vector<int> departures, int __expected) {
    time_t startClock = clock();
    JanuszTheBusinessman *instance = new JanuszTheBusinessman();
    int __result = instance->makeGuestsReturn(arrivals, departures);
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
        vector<int> arrivals;
        from_stream(arrivals);
        vector<int> departures;
        from_stream(departures);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(arrivals, departures, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501408821;
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
        cout << "JanuszTheBusinessman (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
