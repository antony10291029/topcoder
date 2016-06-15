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
int b[5555], aa[5555], c[5555], p[5555];
void solve(int n) {
    for (int i = 0; i < n; ++i) {
        aa[i] = c[i] = p[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        int u = i;
        while ((aa[u] ^ b[u]) != c[u]) {
            int v = p[c[u] ^ b[u]];
            swap(aa[u], aa[v]);
            swap(p[aa[u]], p[aa[v]]);
            if (v > i) break;
            swap(c[i + 1], c[v]);
            u = v;
        }
    }
}
class XorPuzzle {
    public:
    vector<int> find(int k, vector<int> a) {
        int n = a.size();
        int x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= a[i];
        }
        if (n == (1LL<<k)) {
            if (x != 0) {
                vector<int> res;
                res.push_back(-1);
                return res;
            }
        }
        a.push_back(x);
        for (int i = n + 1; i < (1LL << k); ++i) {
            a.push_back(0);
        }
        for (int i = 0; i < (1LL << k); ++i) {
            b[i] = a[i];
        }
        solve(1LL << k);
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            res.push_back(aa[i]);
        }
        for (int i = 0; i < n; ++i) {
            res.push_back(c[i]);
        }
        return res;

        return vector<int>();
    }
};

// CUT begin
ifstream data("XorPuzzle.sample");

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

bool do_test(int k, vector<int> a, vector<int> __expected) {
    time_t startClock = clock();
    XorPuzzle *instance = new XorPuzzle();
    vector<int> __result = instance->find(k, a);
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
        int k;
        from_stream(k);
        vector<int> a;
        from_stream(a);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467340835;
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
        cout << "XorPuzzle (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
