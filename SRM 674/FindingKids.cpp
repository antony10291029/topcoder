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
#define mp make_pair
#define pb push_back      
#define F first
#define S second
#define SS stringstream
#define sqr(x) ((x)*(x))
#define m0(x) memset(x,0,sizeof(x))
#define m1(x) memset(x,63,sizeof(x))
#define CC(x) cout << (x) << endl
#define pw(x) (1ll<<(x))
#define buli(x) __builtin_popcountll(x)
#define M 1000000007
#define N 2000111
#define rep(i,n) for(int i=0;i<n;i++)

using namespace std;
 
int pos[N];
int dir[N];
int kid[N], ti[N];
 
long long ans[N];
int n, q;
 
void sol() {
    vector<int> L, R;
    rep(i,n) if(0 == dir[i]) L.pb(pos[i]); else R.pb(pos[i]);
    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    for (int i = 0; i < q; i++) {
        if (1 == dir[kid[i]]) {
            int x = lower_bound(R.begin(), R.end(), pos[kid[i]]) - R.begin();
            int y = lower_bound(L.begin(), L.end(), pos[kid[i]]) - L.begin();
            int l = 0;
            int r = n + 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                int xx = x - mid / 2;
                int yy = y + (mid + 1) / 2- 1;
                if (xx < 0 || yy >= L.size() || abs(R[xx] - L[yy]) / 2. > ti[i]) r = mid - 1; else l = mid;
            }
            if (l % 2 == 0) {
                ans[i] = abs(R[x - l / 2] + ti[i]);
            } else {
                ans[i] = abs(L[y + (l + 1) / 2 - 1] - ti[i]);
            }
        }
    }
}

class FindingKids {
    public:
    long long getSum(int nn, int qq, int A, int B, int C) {
        n = nn;
        q = qq;
        set<int> was;
        rep(i, n) {
            A = (A * 1ll * B + C) % M;
            int p = A % (M - n + i + 1);
            if (was.find(p) != was.end()) {
                p = M - n + i;
            }
            pos[i] = p;
            was.insert(p);
            if (p % 2 == 0) dir[i] = 1; else dir[i] = 0;
        }
        rep(i, q) {
            A = (A * 1ll * B + C) % M;
            kid[i] = A % n;
            A = (A * 1ll * B + C) % M;
            ti[i] = A;
        }
        sol();
        for (int i = 0; i < n; i++) {
            pos[i] *= -1;
            dir[i] ^= 1;
        }
        sol();
        long long ret = 0;
        rep(i, q) ret += ans[i];
        return ret;
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
