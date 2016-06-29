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
#define N 55
#define R 10
#define K 15000
int n, x, ans, n2;
typedef pair<int,int> PII;
#define FI first
#define SE second
#define MP make_pair
bool cmp (PII p1, PII p2) {
    if (p1.SE * p2.FI - p2.SE * p1.FI != 0) return p1.SE * p2.FI - p2.SE * p1.FI < 0;
    return p1.SE - p2.SE < 0;
}
PII v[N], v2[N];
int cal() {
    int trans = 0, psum = 0;
    for (int i = 0; i < n; ++i) {
        if (i == n / 2) psum += x;
        psum += v2[i].FI;
        trans += psum * v2[i].SE;
    }
    return trans;
}
void go_more_try() {
    srand(123457);
    for (int _ = 0; _ < R; ++_) {
        sort(v, v+n, cmp);
        for (int __ = 0; __ < K; ++__) {
            int ii = rand() % n2;
            int jj = rand() % n2;
            swap( v[ii], v[n2 + jj]);
            for (int i = 0; i < n; ++i) v2[i] = v[i];
            sort(v2, v2+n2, cmp);
            sort(v2+n2, v2+n, cmp);
            int trans = cal();
            if (trans > ans) {
                ans = trans;
                for (int i = 0; i < n; ++i) v[i] = v2[i];
            } else {
                swap(v[ii], v[n2 + jj]);
            }
        }
    }
}
class Moneymanager {
    public:
    int getbest(vector<int> a, vector<int> b, int X) {
        n = (int) a.size();
        n2 = n / 2;
        x = X;
        for (int i = 0; i < n; ++i) {
            v2[i] = v[i] = MP(a[i], b[i]);
        }
        sort(v2, v2+n, cmp);
        ans = cal();
        go_more_try();
        //printf("%d\n", ans);
        return ans;
    }
};

// CUT begin
ifstream data("Moneymanager.sample");

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

bool do_test(vector<int> a, vector<int> b, int X, int __expected) {
    time_t startClock = clock();
    Moneymanager *instance = new Moneymanager();
    int __result = instance->getbest(a, b, X);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        int X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468134699;
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
        cout << "Moneymanager (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
