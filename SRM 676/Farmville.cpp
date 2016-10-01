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

#define REP(i,a) for(int i=0;i<(a);++i)
#define SIZE(x) ((int)(x.size()))
typedef long long int64;

const int maxnode=200000+5;
const int maxedge=1000000+5;
const int oo=2100000000;

int node,src,dest,nedge;
int head[maxnode],point[maxedge],nextp[maxedge],flow[maxedge],capa[maxedge];
int dist[maxnode],Q[maxnode],work[maxnode];

void init(int _node, int _src, int _dest) {
    node = _node;
    src = _src;
    dest = _dest;
    for (int i = 0; i < node; ++i) head[i] = -1;
    nedge = 0;
}

void addedge(int u, int v, int c1, int c2) {
    point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0, nextp[nedge] = head[u]; head[u] = (nedge++);
    point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0, nextp[nedge] = head[v]; head[v] = (nedge++);
}

bool dinic_bfs() {
    for (int i = 0; i < node; ++i) dist[i] = -1;
    dist[src] = 0;
    int sizeQ = 0;
    Q[sizeQ++] = src;
    for (int cl = 0; cl < sizeQ; ++cl) {
        for (int k = Q[cl], i = head[k]; i >= 0; i = nextp[i]) {
            if (flow[i] < capa[i] && dist[point[i]] < 0) {
                dist[point[i]] = dist[k] + 1;
                Q[sizeQ++] = point[i];
            }
        }
    }
    return dist[dest] >= 0;
}

int dinic_dfs(int x, int exp) {
    if (x == dest) return exp;
    int res = 0;
    for (int &i = work[x]; i >= 0; i = nextp[i]) {
        int v = point[i], tmp;
        if (flow[i] < capa[i] && dist[v] == dist[x] + 1 && (tmp = dinic_dfs(v, min(exp,capa[i] - flow[i]))) > 0) {
            flow[i] += tmp;
            flow[i^1] -= tmp;
            res += tmp;
            exp -= tmp;
            if (exp == 0) break;
        }
    }
    return res;
}

int64 dinic_flow() {
    int64 result = 0;
    while (dinic_bfs()) {
        for (int i = 0; i < node; ++i) work[i] = head[i];
        result += dinic_dfs(src, oo);

    }
    return result;
}


class Farmville {
    public:
    int n;
    bool g[60][60];
    int a[60], c[60];
    int o[60],f1[60],f2[60];
    void tpsort() {
        int d[60];
        memset(d, 0, sizeof(d));
        REP(i,n) REP(j,n) if(g[i][j]) d[j]++;
        REP(k,n) {
            int p=0;
            REP(i,n) if (d[i] == 0) { p = i; break; }
            o[k] = p;
            d[p] = -1;
            REP(i, n) if (g[p][i]) --d[i];
        }
    }
    void dfs() {
        memset(f1, 0, sizeof(f1));
        REP(k,n) {
            int p = o[k];
            f1[p] += a[p];
            int e = f1[p];
            REP(i, n) if (g[p][i] && e > f1[i]) f1[i] = e;
        }
        memset(f2, 0, sizeof(f2));
        REP(k, n) {
            int p = o[n - 1 - k];
            f2[p] += a[p];
            int e = f2[p];
            REP(i, n) if (g[i][p] && e > f2[i]) f2[i] = e;
        }
    }
    int solve() {
        int l = f1[n - 1];
        init(n * 2, (n - 2) * 2 + 1, (n - 1) * 2);
        REP(i, n) addedge(i * 2, i * 2 + 1, (a[i] == 0) ? oo : c[i], 0);
        REP(i, n) REP(j, n) if (g[i][j] && f1[i] + f2[j] == l) addedge(i * 2 + 1, j * 2, oo, 0);
        dinic_flow();
        int64  cost = 0;
        REP(i, n) if (dist[i * 2] >= 0 && dist[i * 2 + 1] < 0 && a[i] != 0) { cost += c[i]; --a[i]; }
        return cost;
    }

    int minTime(vector<string> s, vector<int> time, vector<int> cost, int budget) {
        n = SIZE(s);
        memset(g, false, sizeof(g));
        REP(i,n) REP(j,n) g[i][j] = (s[j][i] == '1');
        REP(i,n) a[i] = time[i], c[i] = cost[i];
        REP(i,n) g[n][i] = g[i][n+1] = true;
        a[n] = a[n+1] = 0;
        n+=2;

        tpsort();

        while(1) {
            dfs();
            if (f1[n-1] <= 0) return 0;
            int64 w = solve();
            if (w > budget) break;
            budget -= w;
        }
        return f1[n-1];
        return 0;
    }
};

// CUT begin
ifstream data("Farmville.sample");

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

bool do_test(vector<string> s, vector<int> time, vector<int> cost, int budget, int __expected) {
    time_t startClock = clock();
    Farmville *instance = new Farmville();
    int __result = instance->minTime(s, time, cost, budget);
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
        vector<string> s;
        from_stream(s);
        vector<int> time;
        from_stream(time);
        vector<int> cost;
        from_stream(cost);
        int budget;
        from_stream(budget);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, time, cost, budget, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475293105;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Farmville (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
