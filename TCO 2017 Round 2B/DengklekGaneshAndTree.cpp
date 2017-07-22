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
const int MOD = 1e9 + 7;
struct Vertex {
    int h;
    char c;
    vector<int> edges;
};
struct Segment {
    int a, b;
    Segment(int a = 0) : a(a), b(a + 1) {}
    void add(const Segment &s) {
        a = min(a, s.a);
        b = max(b, s.b);
    }
    bool operator < (const Segment &s) const {
        return a < s.a;
    }
};

class DengklekGaneshAndTree {
    public:
    vector<Vertex> vs;
    vector<bool> was;
    Segment dfs(int u) {
        was[u] = true;
        Segment cur(vs[u].h);
        for (int v : vs[u].edges) {
            if (vs[u].c == vs[v].c) {
                cur.add(dfs(v));
            }
        }
        return cur;
    }
    int getCount(string labels, vector<int> parents) {
        int n = labels.size();
        vs.resize(n);
        for (int i = 0; i < n; ++i) {
            vs[i].c = labels[i];
        }
        int high = 0;
        for (int i = 1; i < n; ++i) {
            int pa = parents[i -1];
            vs[pa].edges.push_back(i);
            vs[i].h = vs[pa].h + 1;
            high = max(high, vs[i].h);
        }
        high = high + 1;
        vector<Segment> a;
        was.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (!was[i]) {
                a.push_back(dfs(i));
            }
        }
        sort(a.begin(), a.end());
        vector<int> dp(high + 1, 0);
        dp[0] = 1;
        for (Segment &s : a) {
            vector<int> cur(dp);
            for (int i = s.a; i <= high; ++i) {
                cur[max(s.b, i)] = (cur[max(s.b, i)] + dp[i]) % MOD;
            }
            dp = cur;
        }

        return dp[high];
    }
};

// CUT begin
ifstream data("DengklekGaneshAndTree.sample");

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

bool do_test(string labels, vector<int> parents, int __expected) {
    time_t startClock = clock();
    DengklekGaneshAndTree *instance = new DengklekGaneshAndTree();
    int __result = instance->getCount(labels, parents);
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
        string labels;
        from_stream(labels);
        vector<int> parents;
        from_stream(parents);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(labels, parents, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500707808;
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
        cout << "DengklekGaneshAndTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
