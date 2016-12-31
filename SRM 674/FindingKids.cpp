#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

const int N = 201000;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;
VI dl, dr;

vector<PII> op;
set<int> ps;

int pp[N];

#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair

int count(ll c, int x) {
    return (lower_bound(all(dr), c - x) - dr.begin()) + (lower_bound(all(dl), c + x) - dl.begin());
}

const ll mod = 1e9 + 7;

class FindingKids {
    public:
    long long getSum(int n, int q, int A, int B, int C) {
        ps.clear(); dr.clear(); dl.clear(); op.clear();
        rep(i, 0, n) {
           A = (A * B + C) % mod;
           ll p = A % (mod - n + i + 1);
           if (ps.count(p)) p = mod - n + i;
           ps.insert(p);
           if (p % 2 == 0) dr.pb(p); else dl.pb(p);
           op.pb(mp(p,i));
        }
        sort(all(dl));
        sort(all(dr));
        sort(all(op));
#define se second
        rep(i, 0, n) pp[op[i].se] = i;
        ll ans = 0;
        rep(i, 0, q) {
            A = (A * B + C) % mod;
            ll kid = A % n;
            A = (A * B + C) % mod;
            ll tm = A;
            ll l = -mod - 1, r = 2 * mod + 1;
            while (l + 1 < r) {
                ll md = (l + r) >> 1;
                if (count(md, tm) > pp[kid]) r = md; else l = md;
            }
            ans += abs(l);
        }
        return ans;
    }
};

// CUT begin
ifstream data("FindingKids.sample");

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

bool do_test(int n, int q, int A, int B, int C, long long __expected) {
    time_t startClock = clock();
    FindingKids *instance = new FindingKids();
    long long __result = instance->getSum(n, q, A, B, C);
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
        int n;
        from_stream(n);
        int q;
        from_stream(q);
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, q, A, B, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483146196;
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
        cout << "FindingKids (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
