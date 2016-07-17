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
#include <queue>

using namespace std;
#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++) 

typedef int F;
#define F_INF (1<<29)
#define MAXV 300
#define MAXE 10000

F cap[MAXE], flow[MAXE];
int to[MAXE], _prev[MAXE], last[MAXV], used[MAXV], level[MAXV];
struct MaxFlow{
    int V, E;
    MaxFlow(int n) {
        int i;
        V = n; E = 0;
        REP(i, V) last[i] = -1;
    }

    void add_edge(int x, int y, F f) {
        cap[E] = f; flow[E] = 0; to[E] = y; _prev[E] = last[x]; last[x] = E; E++;
        cap[E] = 0; flow[E] = 0; to[E] = x; _prev[E] = last[y]; last[y] = E; E++;
    }

    bool bfs(int s, int t) {
        int i;
        REP(i,V) level[i] = -1;
        queue <int> q;
        q.push(s); level[s] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (i = last[x]; i >= 0; i = _prev[i]) if(level[to[i]] == -1 && cap[i] > flow[i]) {
                q.push(to[i]); level[to[i]] = level[x] + 1;
            }
        }
        return (level[t] != -1);
    }
    F dfs(int v, int t, F f) {
        int i;
        if (v == t) return f;
        for (i = used[v]; i >= 0; used[v]=i=_prev[i]) if(level[to[i]] > level[v] && cap[i] >flow[i]) {
            F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
            if (tmp > 0) {flow[i] += tmp; flow[i^1] -= tmp; return tmp;}
        }
        return 0;
    }
    F maxflow(int s, int t) {
        int i;
        while(bfs(s,t)) {
            REP(i,V) used[i] = last[i];
            while (dfs(s, t, F_INF) != 0);
        }
        F ans = 0;
        for (i=last[s]; i >= 0; i = _prev[i]) ans += flow[i];
        return ans;
    }
};
int delta[210];
class SRMDiv0Easy {
    public:
    int get(int N, vector<int> L, vector<int> R, vector<int> X, vector<int> Y) {
        int i;
        MaxFlow mf(N+3);
        mf.add_edge(N+1, 0, 0);
        mf.add_edge(N, N+2, 0);
        REP(i,L.size()) {
            mf.add_edge(L[i], R[i]+1, Y[i]-X[i]);
            delta[L[i]] += X[i];
            delta[R[i] + 1] -= X[i];
        }
        int S = 0;
        REP(i,N+1) {
            if (delta[i] > 0) {
                mf.add_edge(i, N+2, delta[i]);
                S += delta[i];
            } else if (delta[i] < 0) {
                mf.add_edge(N+1, i, -delta[i]);
            }
        }
        int ans = -1;
        REP(i,200010){
            if(mf.maxflow(N+1,N+2) == S + i) ans = i;
            cap[0]++;
            cap[2]++;
        }
        return ans;
    }
};

// CUT begin
ifstream data("SRMDiv0Easy.sample");

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

bool do_test(int N, vector<int> L, vector<int> R, vector<int> X, vector<int> Y, int __expected) {
    time_t startClock = clock();
    SRMDiv0Easy *instance = new SRMDiv0Easy();
    int __result = instance->get(N, L, R, X, Y);
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
        vector<int> L;
        from_stream(L);
        vector<int> R;
        from_stream(R);
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, L, R, X, Y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468737157;
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
        cout << "SRMDiv0Easy (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
