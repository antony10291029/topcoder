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
#define REP(i,a) for(int i = 0; i < (a); ++i)
class HardProof {
    public:
    int a[51][51], g[51][51];
    int N;
    bool can(int low, int high) {
        REP(i,N) REP(j,N) {
            g[i][j] = (i == j);
            if (a[i][j] >= low && a[i][j] <= high) {
                g[i][j] = 1;
            }
        }
        REP(k, N) REP(i, N) if (g[i][k]) REP(j, N) if (g[i][k] == 1 && g[k][j] == 1) g[i][j] = 1;
        REP(i, N) REP(j, N) if (g[i][j] == 0) return false;
        return true;
    }
    int minimumCost(vector<int> D) {
        N = 0;
        while (N * N < D.size()) ++N;
        if (N <= 1) return 0;
        REP(i,N) REP(j,N) a[i][j] = D[i*N+j];
        vector<int> v(D.begin(), D.end());
        sort(v.begin(), v.end());
        vector<int> t;
        for (int i = 0; i < v.size(); ++i) {
            if (i == 0 || v[i] != v[i-1]) t.push_back(v[i]);
        }
        int ans = 0x7f7f7f7f;
        for (int i = 0, j = 0; i < t.size(); ++i) {
            while (j < t.size() && !can(t[i], t[j])) ++j;
            if (j < t.size()) ans = min(ans, t[j] - t[i]);
        }
        return ans;
    }
};

// CUT begin
ifstream data("HardProof.sample");

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

bool do_test(vector<int> D, int __expected) {
    time_t startClock = clock();
    HardProof *instance = new HardProof();
    int __result = instance->minimumCost(D);
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
        vector<int> D;
        from_stream(D);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(D, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467103557;
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
        cout << "HardProof (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
