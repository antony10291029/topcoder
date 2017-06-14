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
typedef long long ll;
ll bit(int x) {
    return 1ll << x;
}
const int M = 55;
vector<int> g[M];
const int MX = 100000000;
int v[MX], step[MX], go[MX], ct[MX];
map<int, int> S;
class WalkOverATree {
    public:

    int maxNodesVisited(vector<int> parent, int L) {
        cout << "L="<< L<<endl;
        if (parent.size() == 0) {
            return 1;
        }
        int n = parent.size() + 1;
        for (int i = 0; i < n-1; ++i) {
            int chi = i + 1;
            int par = parent[i];
            g[chi].push_back(par);
            g[par].push_back(chi);
        }
        ll all = 0;
        for (int i = 0; i < n; ++i) all |= bit(i);



        int front = 0, tail = 0;
        go[front] = bit(0); ct[front] = 1;
        S[bit(0)] = 1;
        step[front] = 0;
        v[front++] = 0;
        while (tail < front) {
            int _bit = go[tail], _ct = ct[tail],  _v = v[tail], _step = step[tail++];
            //cout << "_v=" << _v << ",_step=" << _step << ",_ct=" << _ct << ",tail=" << tail<<endl;
            if (_step >= L) break;
            for (int i = 0; i < g[_v].size(); ++i) {
                int nxt = g[_v][i];
                go[front] = (_bit | bit(nxt));
                if ((_bit & bit(nxt)) == 0) ct[front] = _ct + 1; else ct[front] = _ct;
                v[front] = nxt;
                if (S[go[front]]!=0 && S[go[front]] < ct[front]) {cout<<"coutinue" << endl;continue;}
                cout << "S[go[front]]=" << S[go[front]] << ",ct[front]=" << ct[front] << ",ok=" << (S[go[front]]!=0 && S[go[front]] < ct[front])<<endl;
                S[go[front]]=ct[front];
                step[front++] = _step + 1;
            }
            if (front % 10000000 == 0) cout << front<<endl;
        }
        int res = 0;
        cout << front << endl;
        for (int i = 0; i < front; ++i) if (ct[i] > res) {
            res = ct[i];
        }

        return res;
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
