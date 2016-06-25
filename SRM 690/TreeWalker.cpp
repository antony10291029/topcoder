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
#define ADD(X,Y) ((X) = ((X) + (Y) % MOD) % MOD)
typedef long long ll;

const int MOD = 1e9 + 7;

int Ai[101010];
vector<int> graph[101010];

ll pow2[101010], rev2[101010];
int sz[101010];

int calc_sz(int p, int rt) {
    sz[p] = 1;
    for (int q : graph[p]) if (q != rt) {
        sz[p] += calc_sz(q, p);
    }
    return sz[p];
}

pair<ll, pair<ll, ll> > dfs(int p, int rt) {
    ll in = 0, out = 0, tot = 0;
    vector<ll> ins, outs;
    vector<int> ch;
    for (int q : graph[p]) if (q != rt) {
        auto tmp = dfs(q, p);
        ADD(tot, tmp.first * pow2[sz[p] - sz[q]]);

        ll tin = tmp.second.first, tout = tmp.second.second;
         ADD(tin, pow2[sz[q] - 1]);
         ADD(tout, pow2[sz[q] - 1]);
         ins.push_back(tin);
         outs.push_back(tout);
         ch.push_back(q);
    }
    
    for (int i = 0; i < ins.size(); ++i) {
        int q = ch[i];
        ins[i] = ins[i] * rev2[sz[q]] % MOD;
        outs[i] = outs[i] * rev2[sz[q]] % MOD;
    }
    ll insum = 0, outsum = 0;
    for (int i = 0; i < ins.size(); ++i) {
        ADD(insum, ins[i]);
        ADD(outsum, outs[i]);
    }
    
    ll cur = 0;
    for (int i = 0; i < ins.size(); ++i) {
        ADD(cur, MOD - ins[i] * outs[i] % MOD);
    }
    ADD(cur, insum * outsum);
    cur = cur * pow2[sz[p] - 1] % MOD;

    for (int i = 0; i < ins.size(); ++i) {
        int q = ch[i];
        ADD(in, ins[i] * pow2[sz[p] - 1]);
        ADD(out, outs[i] * pow2[sz[p] - 1]);
    }
    tot = (tot + cur + in + out) % MOD;
    return make_pair(tot, make_pair(in, out));
}

class TreeWalker {
    public:
    int calc(int N, int A0, int B, int C, int MOD) {
        Ai[0] = A0;
        for (int i = 1; i <= N - 2; ++i) {
            Ai[i] = ((ll) Ai[i - 1] * B + C) % MOD;
        }
        for (int i = 0; i < N; ++i) graph[i].clear();
        for (int i = 1; i <= N - 1; ++i) {
            int j = Ai[i - 1] % i;
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
        
        pow2[0] = rev2[0] = 1;
        for (int i = 1; i <= N; ++i) {
            pow2[i] = pow2[i - 1] * 2 % ::MOD;
            rev2[i] = rev2[i - 1] * ((::MOD + 1) / 2) % ::MOD;
        }

        calc_sz(0, -1);
        auto ret = dfs(0, -1);
        return ret.first;
    }
};

// CUT begin
ifstream data("TreeWalker.sample");

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

bool do_test(int N, int A0, int B, int C, int MOD, int __expected) {
    time_t startClock = clock();
    TreeWalker *instance = new TreeWalker();
    int __result = instance->calc(N, A0, B, C, MOD);
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
        int A0;
        from_stream(A0);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        int MOD;
        from_stream(MOD);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, A0, B, C, MOD, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1466844004;
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
        cout << "TreeWalker (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
