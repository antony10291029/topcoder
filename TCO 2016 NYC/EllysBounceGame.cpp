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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (n); ++i)
class EllysBounceGame {
    public:
    long long getScore(vector<int> tiles) {
        int N = tiles.size();
        vector<ll> cuml(N + 1), cumr(N + 1);
        REP(i, N) {
            cuml[i + 1] = cuml[i] + tiles[i];
            cumr[N - i - 1] = cumr[N - i] + tiles[N - i - 1];
        }
        ll res = 0;
        REP(i, N) {
            vector<int> lt, rt;
            for (int j = i - 1; j >= 0; --j) {
                if (tiles[j] % 2 == 1) {
                    lt.push_back(j);
                }
            }
            lt.push_back(-1);
            for (int j = i + 1; j <= N - 1; ++j) {
                if (tiles[j] % 2 == 1) {
                    rt.push_back(j);
                }
            }
            rt.push_back(N);
            REP(dir, 2) {
                ll cres = tiles[i];
                int p = i;
                int d = dir;
                int l = 0, r = 0;
                while (p >= 0 && p < N) {
                    if (d == 0) {
                        int np = rt[r];
                        cres += cuml[min(np+1, N)] - cuml[p+1];
                        cres += max(r + l - 1, 0);
                        if (l || r) cres += tiles[i] % 2;
                        p = np;
                        ++r;
                    } else {
                        int np = lt[l];
                        cres += cumr[max(0, np)] - cumr[p];
                        cres += max(r + l - 1, 0);
                        if (l || r) cres += tiles[i] % 2;
                        p = np;
                        ++l;
                    }
                    d = 1 - d;
                }
                res = max(cres, res);
            }
        }
        return res;
    }
};

// CUT begin
ifstream data("EllysBounceGame.sample");

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

bool do_test(vector<int> tiles, long long __expected) {
    time_t startClock = clock();
    EllysBounceGame *instance = new EllysBounceGame();
    long long __result = instance->getScore(tiles);
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
        vector<int> tiles;
        from_stream(tiles);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tiles, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1470150614;
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
        cout << "EllysBounceGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
