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
const int M = 256;
bool g[M][M];
bool vis[M];
int q[M];
#define clr(x) memset(x, 0, sizeof(x))
#define rep(i,a) for(int i = 0; i < (a); ++i)
#define per(i,a,b) for(int i = (a); i < (b); ++i)

class ScoresSequence {
    public:
    int count(vector<int> s) {
        int n = s.size();
        clr(g);
        rep(i,n) g[i][i] = true;
        clr(vis);
        rep(step, n) {
            int k = -1;
            rep(i,n) if (!vis[i] && (k == -1 || s[i] > s[k])) k = i;
            vis[k] = true;
            int cnt = 0;
            rep(i,n) if (!vis[i]) q[cnt++] = i;
            sort(q, q+cnt,[&](int a,int b) { return s[a]>s[b]; });
            int wcnt = n - 1 - step - s[k];
            rep(i,wcnt) g[q[i]][k] = true, --s[q[i]];
            per(i,wcnt,cnt) g[k][q[i]] = true;
        }
        rep(k,n) rep(i,n) rep(j,n) if (g[i][k] && g[k][j]) g[i][j] = true;
        int res = 0;
        rep(i,n) rep(j,n) if (g[i][j]) ++res;
        return res;
    }
};

// CUT begin
ifstream data("ScoresSequence.sample");

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

bool do_test(vector<int> s, int __expected) {
    time_t startClock = clock();
    ScoresSequence *instance = new ScoresSequence();
    int __result = instance->count(s);
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
        vector<int> s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499007111;
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
        cout << "ScoresSequence (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
