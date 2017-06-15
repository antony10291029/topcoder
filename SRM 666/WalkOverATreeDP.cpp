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
#include <map>
using namespace std;
#define SZ(X) (X.size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define min(x, y) ((x) < (y)) ? (x) : (y)
#define max(x, y) ((x) > (y)) ? (x) : (y)
vector<int> adj[105];
int sz[105], dp[105][105];
int L, N;
void dfs(int u) {
    sz[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
    rep(i, L + 1) {
        dp[u][i] = 1;
        rep(j, L + 1) {
            if (j > i) continue;
            for (int v : adj[u]) {
                int tmp = min(sz[u] - 1 - sz[v], (i - j) / 2) + 1;
                if (j - 1 >= 0) tmp += dp[v][j - 1];
                dp[u][i] = max(dp[u][i], tmp);
            }

        }
    }
}
using namespace std;
class WalkOverATree {
    public:

    int maxNodesVisited(vector<int> parent, int L) {
        for (int i = 0; i < 105; ++i)adj[i].clear();memset(sz, 0, sizeof(sz)); memset(dp, 0, sizeof(dp));
        ::L = L;
        N = parent.size() + 1;
        for (int i = 0; i < N - 1; i++) {
            adj[parent[i]].push_back(i + 1);
        }
        dfs(0);
        return dp[0][L];
    }
};

// CUT begin
ifstream data("WalkOverATree.sample");

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

bool do_test(vector<int> parent, int L, int __expected) {
    time_t startClock = clock();
    WalkOverATree *instance = new WalkOverATree();
    int __result = instance->maxNodesVisited(parent, L);
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
        vector<int> parent;
        from_stream(parent);
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(parent, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496799702;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 222 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WalkOverATree (222 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
