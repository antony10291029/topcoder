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
#define rep(i,a,b) for(int i = (a); i <(b); ++i)
const int N = 55;
int _r[N], _c[N], g[N][N];
#define fi first
#define se second
#define mp make_pair
class GridSortMax {
    public:
    string findMax(int r, int c, vector<int> grid) {
        rep(i,0,N) _r[i] = _c[i] = 0;
        pair<int,int>pos[r*c];
        for (int i = 0; i < r; i++) {
            //cerr<<endl;
            for (int  j = 0; j < c; ++j) {
                g[i][j] = grid[i*c+j] - 1;
                //cerr<<g[i][j]<<' ';
                pos[g[i][j]] = mp(i,j);
            }
        }
        string res = "";
        for (int val = 0; val < r*c; ++val) {
            int tr = val / c, tc = val % c;
            int sr = pos[val].fi, sc = pos[val].se;
            if (tr == sr && tc == sc) {
                res += '1';
                _r[tr] = _c[tc] = 1;
            } else {
                if (tr == sr || (!_r[tr] && !_r[sr])) {
                    if (tc == sc || (!_c[tc] && !_c[sc])) {
                        rep(rr,0,r) swap(g[rr][tc],g[rr][sc]);
                        rep(cc,0,c) swap(g[tr][cc],g[sr][cc]);
                        for (int i = 0; i < r; ++i) {
                            for (int j = 0; j < c; ++j) {
                                pos[g[i][j]] = mp(i,j);
                            }
                        }
                    }
                }
                if (g[tr][tc] == val) {
                    res += '1';
                    _r[tr] = _c[tc] = 1;
                } else {
                    res += '0';
                }
            }
        }


        return res;
    }
};

// CUT begin
ifstream data("GridSortMax.sample");

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

bool do_test(int n, int m, vector<int> grid, string __expected) {
    time_t startClock = clock();
    GridSortMax *instance = new GridSortMax();
    string __result = instance->findMax(n, m, grid);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        vector<int> grid;
        from_stream(grid);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493392367;
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
        cout << "GridSortMax (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
