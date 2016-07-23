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
#define REP(i,n) for(i=0;i<n;++i)
bool deg[2010];
int N;
vector <pair <int, pair <int, int> > > v;
vector <int> graph[2010];
bool used[2010];
bool same(int x, int y) {
    return (x == y && x != -1);
}
bool can_take(int x) {
    int a= v[x].second.first;
    if (a != -1 && used[a]) return false;
    a = v[x].second.second;
    if (a != -1 && used[a]) return false;
    return true;
}
void take(int x) {
    int a = v[x].second.first;
    if (a != -1) used[a] = true;
    a = v[x].second.second;
    if (a != -1) used[a] = true;
}
void untake(int x) {
    int a = v[x].second.first;
    if (a != -1) used[a] = false;
    a = v[x].second.second;
    if (a != -1) used[a] = false;
}
int dfs(int pos, int K) {
    int i;
    if (K == 0 || pos == N) return 0;
    if (!can_take(pos)) return dfs(pos + 1, K);

    take(pos);
    int ans = dfs(pos + 1, K - 1) + v[pos].first;
    untake(pos);

    REP(i, graph[pos].size()) {
        int x = graph[pos][i];
        if (can_take(x)) {
            take(x);
            int tmp = dfs(pos + 1, K - 1) + v[x].first;
            untake(x);
            ans = max(ans, tmp);
        }
    }
    return ans;
}
class BearKRoads {
    public:
    int maxHappy(vector<int> x, vector<int> a, vector<int> b, int KK) {
        int i, j;

        REP(i, a.size()) deg[a[i]] = deg[b[i]] = true;

        REP(i, a.size()) v.push_back(make_pair(x[a[i]] + x[b[i]], make_pair(a[i], b[i])));
        REP(i, x.size()) if (deg[i]) v.push_back(make_pair(x[i], make_pair(i, -1)));

        N = v.size();
        int K = min(N, KK);
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());

        REP(i,N) REP(j,N) if (i != j) {
            int p1 = v[i].second.first;
            int p2 = v[i].second.second;
            int q1 = v[j].second.first;
            int q2 = v[j].second.second;
            if (same(p1, q1) || same(p1, q2) || same(p2, q1) || same(p2,q2)) graph[i].push_back(j);
        }
        int ans = dfs(0, K);
        return ans;
    }
};

// CUT begin
ifstream data("BearKRoads.sample");

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

bool do_test(vector<int> x, vector<int> a, vector<int> b, int K, int __expected) {
    time_t startClock = clock();
    BearKRoads *instance = new BearKRoads();
    int __result = instance->maxHappy(x, a, b, K);
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
        vector<int> x;
        from_stream(x);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, a, b, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469205342;
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
        cout << "BearKRoads (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
