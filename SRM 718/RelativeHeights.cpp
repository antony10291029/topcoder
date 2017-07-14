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
const int MX = 55;
int q[MX];
int idx[MX];
int val[MX][MX];
#define sz(n) (n).size()
#define rep(i,n) for(int i = 0; i < (n); ++i)
class RelativeHeights {
    public:
    int countWays(vector<int> h) {
        int n = sz(h);
        rep(i,n) {
            int cnt = 0;
            rep(j,n) {
                if (j != i) {
                    q[cnt++] = j;
                }
            }
            sort(q, q+cnt,[&](int a, int b) { return h[a] > h[b]; });
            rep(j,cnt) {
                idx[q[j]] = j;
            }
            cnt = 0;
            rep(j,n) {
                if (j != i) {
                    val[i][cnt++] = idx[j];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int ok = 1;
            for (int j = i+1; j < n; ++j) {
                int flag = 0;
                for (int k = 0; k < n-1; ++k) {
                    if (val[i][k] != val[j][k]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ok = 0;
                    break;
                }
            }
            if (ok) res++;
        }
        return res;
    }
};

// CUT begin
ifstream data("RelativeHeights.sample");

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

bool do_test(vector<int> h, int __expected) {
    time_t startClock = clock();
    RelativeHeights *instance = new RelativeHeights();
    int __result = instance->countWays(h);
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
        vector<int> h;
        from_stream(h);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(h, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499994980;
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
        cout << "RelativeHeights (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
