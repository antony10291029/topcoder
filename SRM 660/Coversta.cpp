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
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define in(x,y) (x >= 0 && x < r && y >= 0 && y < c)
#define clr(x) memset(x, 0, sizeof(x))
const int MX = 101;
int s[MX][MX], f[MX][MX];
class Coversta {
    public:
    int place(vector<string> a, vector<int> x, vector<int> y) {
        int r = a.size(), c = a[0].size(), n = x.size();
        clr(s);
        rep(i,0,r) rep(j,0,c) {
            rep(k,0,n) {
                int nx = i + x[k];
                int ny = j + y[k];
                if (in(nx, ny)) {
                    s[i][j] += a[nx][ny] - '0';
                }
            }
        }
        int res = 0;
        rep(i,0,r) rep(j,0,c) {
            memcpy(f,s,sizeof(f));
            rep(k,0,n) {
                int target_x = i + x[k];
                int target_y = j + y[k];
                if (in(target_x, target_y)) {
                    rep(k2,0,n) {
                        int src_x = target_x - x[k2];
                        int src_y = target_y - y[k2];
                        if (in(src_x, src_y)) {
                            f[src_x][src_y] -= a[target_x][target_y] - '0';
                        }
                    }
                }
            }
            rep(f_x,0,r)rep(f_y,0,c) {
                res = max(res, f[f_x][f_y] + s[i][j]);
            }
        }
        return res;
    }
};

// CUT begin
ifstream data("Coversta.sample");

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

bool do_test(vector<string> a, vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    Coversta *instance = new Coversta();
    int __result = instance->place(a, x, y);
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
        vector<string> a;
        from_stream(a);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498300760;
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
        cout << "Coversta (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
