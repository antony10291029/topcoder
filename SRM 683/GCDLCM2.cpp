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
#define REP(i,n) for(int i=0;i<n;++i)
const int md = 1e9 + 7;
const int MAX = 1e7 + 10;
const int N = 1e6 + 10;
int prime[MAX];
int pos[MAX];
int who[N];
vector<int> z[N];
int res[N];

class GCDLCM2 {
    public:
    int getMaximalSum(vector<int> start, vector<int> d, vector<int> cnt);
};
int GCDLCM2::getMaximalSum(vector<int> start, vector<int> d, vector<int> cnt) {
    REP(i,MAX) prime[i]=i;
    for (int i = 2; i * i < MAX; ++i) {
        if (prime[i] == i) {
            for (int j = i * i; j < MAX; j += i) {
                if (prime[j] == j) prime[j] = i;
            }
        }
    }
    int t = 0;
    for (int i = 2; i < MAX; ++i) {
        if (prime[i] == i) {
            who[t] = i;
            pos[i] = t;
            z[t].clear();
            t++;
        }
    }
    int cnts = start.size();
    int n = 0;
    for (int id = 0; id < cnts; ++id) {
        for (int u = 0; u < cnt[id]; ++u) {
            res[n++] = 1;
            int num = start[id] + u * d[id];
            while (num > 1) {
                int div = prime[num];
                int pw = 0;
                while (prime[num] == div) {
                    num /= div;
                    ++pw;
                }
                z[pos[div]].push_back(pw);
            }
        }
    }
    for (int i = 0; i < t; ++i) {
        sort(z[i].rbegin(), z[i].rend());
        //sort(z[i].begin(), z[i].end());
        //reverse(z[i].begin(), z[i].end());

        int at = 0;
        for (int j = 0; j < (int) z[i].size(); ++j) {
            int tmp = 1;
            for (int k = 0; k < z[i][j]; ++k) {
                tmp *= who[i];
            }
            res[at] = (long long) res[at] * tmp % md;
            ++at;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + res[i]) % md;
    }
    return ans;
}

// CUT begin
ifstream data("GCDLCM2.sample");

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

bool do_test(vector<int> start, vector<int> d, vector<int> cnt, int __expected) {
    time_t startClock = clock();
    GCDLCM2 *instance = new GCDLCM2();
    int __result = instance->getMaximalSum(start, d, cnt);
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
        vector<int> start;
        from_stream(start);
        vector<int> d;
        from_stream(d);
        vector<int> cnt;
        from_stream(cnt);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(start, d, cnt, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469407068;
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
        cout << "GCDLCM2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
