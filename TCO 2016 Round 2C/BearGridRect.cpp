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
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,a) FOR(i,0,a)
#define SIZE(X) ((int)(X.size()))
const int maxnode = 200005;
const int maxedge = 1000005;
const int oo = (int) 1e9;
int node,src,dest,nedge;
int head[maxnode],point[maxedge],nextp[maxedge],flow[maxedge],capa[maxedge];
int distp[maxnode], Q[maxnode], work[maxnode];
void init(int _node, int _src, int _dest) {
    node = _node;
    src = _src;
    dest = _dest;
    for (int i = 0; i < node; ++i) head[i] = -1;
    nedge=0;
}
void addedge(int u, int v, int c1, int c2) {
    point[nedge] = v; capa[nedge] = c1; flow[nedge]=0; nextp[nedge]=head[u]; head[u] = (nedge++);
    point[nedge] = u; capa[nedge] = c2; flow[nedge]=0; nextp[nedge]=head[v]; head[v] = (nedge++);
}
bool dinic_bfs() {
    for (int i = 0; i < node; ++i) distp[i] = -1;
    distp[src]=0;
    int sizeQ=0;
    Q[sizeQ++]=src;
    for (int c1 = 0; c1 < sizeQ; ++c1) {
        int k = Q[c1];
        for (int i=head[k]; i >= 0; i = nextp[i]) if (flow[i] < capa[i] && distp[point[i]] < 0) {
            distp[point[i]] = distp[k] + 1;
            Q[sizeQ++]=point[i];
        }
    }
    return distp[dest] >= 0;
}
int dinic_dfs(int x, int exp) {
    if (x == dest) return exp;
    int res = 0;
    for (int &i=work[x]; i >= 0; i = nextp[i]) {
        int v = point[i], tmp;
        if (flow[i] < capa[i] && distp[v] == distp[x] + 1 && (tmp = dinic_dfs(v, min(exp, capa[i]-flow[i]))) > 0) {
            flow[i] += tmp;
            flow[i^1] -= tmp;
            res += tmp;
            exp -= tmp;
            if (exp == 0) break;
        }
    }
    return res;
}
int dinic_flow() {
    int result = 0;
    while (dinic_bfs()) {
        for (int i = 0; i < node; ++i) work[i] = head[i];
        result += dinic_dfs(src, oo);
    }
    return result;
}
int dinic_flow(int s, int t) {
    src = s;
    dest = t;
    return dinic_flow();
}
class BearGridRect {
    public:
    int n,m;
    int src, dst, g_src, g_dst;
    void add(int a, int b, int c1, int c2) {
        if (c1 > 0) {
            addedge(g_src, b, c1, 0);
            addedge(a, g_dst, c2, 0);
        }
        if (c1 < c2) {
            addedge(a,b,c2-c1,0);
        }
    }
    int get_flow(int a, int b) {
        for(int p=head[a];p>=0;p=nextp[p]) if (point[p] == b) return flow[p];
        return 0;
    }
    vector<int> findPermutation(int N, vector<int> r1, vector<int> r2, vector<int> c1, vector<int> c2, vector<int> cnt) {
        n=N;
        m=SIZE(r1);
        init(2*n+2*m+4,0,1);
        src=2*n+2*m;
        dst=2*n+2*m+1;
        g_src=2*n+2*m+2;
        g_dst=2*n+2*m+3;
        REP(i,n) add(src,i,1,1);
        REP(i,n) add(i+n,dst,1,1);
        int e[64][64];
        memset(e,-1,sizeof(e));
        REP(i,m) for(int x = r1[i]; x <= r2[i]; ++x) for (int y=c1[i]; y <= c2[i]; ++y) e[x][y] = i;
        REP(x,n) REP(y,n) {
            if (e[x][y] < 0) {
                add(x,y+n,0,1);
            } else {
                add(x, 2*n+e[x][y],0,1);
                add(2*n+m+e[x][y],n+y,0,1);
            }
        }
        REP(i,m) add(2*n+i,2*n+m+i, cnt[i], cnt[i]);
        addedge(dst,src,1000000,1000000);
        dinic_flow(g_src, g_dst);
        for(int p=head[g_src];p>=0;p=nextp[p])if(flow[p]<capa[p]) {
            vector<int> ret;
            ret.push_back(-1);
            return ret;
        }
        vector<int> ret;
        REP(i,n) ret.push_back(-1);
        REP(x,n) REP(y,n) if (e[x][y] < 0 && get_flow(x,y+n)==1) ret[x]=y;
        REP(i,m) if(cnt[i] > 0) {
            vector<int>px,py;
            REP(x,n) if (get_flow(x,2*n+i) == 1) px.push_back(x);
            REP(y,n) if (get_flow(2*n+m+i,n+y) == 1) py.push_back(y);
            REP(k,SIZE(px)) ret[px[k]] = py[k];
        }
        return ret;






        return vector<int>();
    }
};

// CUT begin
ifstream data("BearGridRect.sample");

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

bool do_test(int N, vector<int> r1, vector<int> r2, vector<int> c1, vector<int> c2, vector<int> cnt, vector<int> __expected) {
    time_t startClock = clock();
    BearGridRect *instance = new BearGridRect();
    vector<int> __result = instance->findPermutation(N, r1, r2, c1, c2, cnt);
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
        vector<int> r1;
        from_stream(r1);
        vector<int> r2;
        from_stream(r2);
        vector<int> c1;
        from_stream(c1);
        vector<int> c2;
        from_stream(c2);
        vector<int> cnt;
        from_stream(cnt);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, r1, r2, c1, c2, cnt, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468975135;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BearGridRect (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
