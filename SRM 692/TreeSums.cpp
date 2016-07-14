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
typedef pair<int, ll> pil;
#define mp make_pair
const int N = 300300;
int n;
ll ans = 0;
vector<int> g[N];
int par[N];
ll lenToPar[N];
int cntr[N];
ll sumLenToCntr[N];
ll sumLenToRoot[N];
   
ll h[N];
int sz[N];

void genTree(ll x, ll C, ll D) {

    for (int i = 0; i < n; ++i) g[i].clear(),par[i]=0,lenToPar[i]=0;

    for (int i = 1; i < n; ++i) {
        x = (C * x + D) % (ll) 1e9;
        par[i] = x % i;
        x = (C * x + D) % (ll) 1e9;
        lenToPar[i] = x % (ll) 1e6;
    }
    for (int i = 1; i < n; ++i) {
        g[par[i]].push_back(i);
    }
    return;
}
void precalc() {
    ans = 0;
    memset(h, 0, sizeof(h));
    memset(cntr, 0, sizeof(cntr));
    memset(sumLenToCntr, 0, sizeof(sumLenToCntr));
    memset(sumLenToRoot, 0, sizeof(sumLenToRoot));
    for (int i = 0; i < n; ++i) sz[i] = 1;
    h[0] = 0;
    for (int i = 1; i < n; ++i) {
        h[i] = h[par[i]] + lenToPar[i];
    }
    for (int i = n - 1; i > 0; --i) {
        sz[par[i]] += sz[i];
    }
    return;
}
void solve(int v) {
    if (g[v].empty()) {
        cntr[v] = v;
        return;
    }
    sumLenToRoot[v] = 0;
    for (int u : g[v]) {
        sumLenToRoot[v] += sumLenToRoot[u] + sz[u] * lenToPar[u];
    }
    int U = -1;
    for (int u : g[v]) {
        if (2 * sz[u] > sz[v]) {
            U = u;
        }
    }
    if (U == -1) {
        sumLenToCntr[v] = sumLenToRoot[v];
        cntr[v] = v;
        return;
    }
    int w = cntr[U];
    sumLenToCntr[v] = sumLenToCntr[U] + (sumLenToRoot[v] - sumLenToRoot[U] - sz[U] * lenToPar[U]) + (sz[v] - sz[U]) * (h[w] - h[v]);
    while (2 * sz[w] <= sz[v]) {
        sumLenToCntr[v] -= (sz[v] - 2 * sz[w]) * lenToPar[w];
        w = par[w];
    }
    cntr[v] = w;
    return;
}
void solve() {
    precalc();
    for (int i = n - 1; i >= 0; --i) {
        solve(i);
    }
    for (int i = 0; i < n; ++i) {
        ans ^= sumLenToCntr[i];
    }
    return;
}



class TreeSums {
    public:
    long long findSums(int NN, int seed, int C, int D) {
        n = NN;
        genTree(seed, C, D);
        solve();
        return ans;
    }
};

// CUT begin
ifstream data("TreeSums.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int seed, int C, int D, long long __expected) {
    time_t startClock = clock();
    TreeSums *instance = new TreeSums();
    long long __result = instance->findSums(N, seed, C, D);
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
        int N;
        from_stream(N);
        int seed;
        from_stream(seed);
        int C;
        from_stream(C);
        int D;
        from_stream(D);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, seed, C, D, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468412183;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TreeSums (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
