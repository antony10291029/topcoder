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
#define REP(i,a,b) for(int i=(a); i< (b); ++i)
using namespace std;
void mv(int *a, int x, int n) {
    int y = a[x];
    a[x] = 0;
    REP(i, 0, y) {
        x = (x + 1) % n;
        a[x] += 1;
    }

}
const int N = 15;
int A[N];
int B[N];
vector<int> res[2];
void solve(int idx, int *a, int n) {
    int sum = 0;
    REP(i,0,n) {
        sum+=a[i];
    }
    while(a[0] != sum) {
        for (int i = 1; i < n; ++i) if (a[i]>0) {
            if (idx == 0) {
                res[idx].push_back(i);
                mv(a, i, n);
            } else {
                res[idx].push_back((i+a[i]) % n);
                mv(a, i, n);
            }
            break;
        }
    }
}
class ReverseMancala {
    public:
    vector<int> findMoves(vector<int> start, vector<int> target) {
        REP(i,0,start.size()) {
            A[i] = start[i];
            B[i] = target[i];
        }
        solve(0, A, start.size());
        solve(1, B, target.size());
        vector<int> r;
        REP(i,0,res[0].size()) {
            r.push_back(res[0][i]);
        }
        reverse(res[1].begin(), res[1].end());
        REP(i,0,res[1].size()) {
            r.push_back(res[1][i] + start.size());
        }
        return r;
    }
};

// CUT begin
ifstream data("ReverseMancala.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> start, vector<int> target, vector<int> __expected) {
    time_t startClock = clock();
    ReverseMancala *instance = new ReverseMancala();
    vector<int> __result = instance->findMoves(start, target);
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
        vector<int> target;
        from_stream(target);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(start, target, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1492941536;
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
        cout << "ReverseMancala (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
