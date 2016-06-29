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
#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
typedef long long ll;
int X, Y;
int a[60][60];

bool isp[70], isq[70];
int c[60][60][60][60];
int one[60][60];
ll freq[1024*1024];
ll sum[1024*1024];


class Undivisors {
    public:
    ll convolution(int K) {
        int i,j;
        REP(i,(1<<K)) sum[i] = freq[i];
        REP(i,K) REP(j,(1<<K)) if (!(j&(1<<i))) sum[j|(1<<i)] += sum[j];
        ll ans = 0;
        REP(i, (1<<K)) {
            int c = 1;
            if (__builtin_popcount(i) % 2 != K % 2) c = -1;
            ans += c * sum[i] * sum[i];
        }
        return ans;
    }
    ll func(int m) {
        int i,j,k,l;
        if (m == 64) return 0;
        vector<int> v;
        for (i=2;i<=m;++i) if (isp[i]) {
            int q = 1;
            while (q * i <= m) q *= i;
            v.push_back(q);
        }
        int K = v.size();
        REP(i,X) REP(j,Y) one[i][j] = 0;
        REP(i,X) REP(j,Y) REP(k,K) if (a[i][j] % v[k] == 0) one[i][j] += (1<<k);
        REP(i,(1<<K)) freq[i] = 0;
        REP(i,X+1) REP(j,Y+1) for (k=i+1;k<=X;++k) for (l=j+1;l<=Y;++l) {
            c[i][j][k][l] = (c[i][j][k-1][l] | c[i][j][k][l-1] | one[k-1][l-1]);
            ++freq[c[i][j][k][l]];
        }
        ll ans = convolution(K);
        return ans;
    }
    double getexp(vector<string> aa) {
        int i, j;
        X = aa.size();
        Y = aa[0].length();
        REP(i, X) REP(j,Y) {
            char c = aa[i][j];
            if (c >= '1' && c <= '9') a[i][j] = c - '0';
            else if (c >= 'A' && c <= 'Z') a[i][j] = c - 'A' + 10;
            else if (c >= 'a' && c <= 'z') a[i][j] = c - 'a' + 36;
        }
        for (i=2;i<70;++i)isp[i]=true;
        for (i=2;i<70;++i) {
            if(isp[i]) {
                for (j=2*i;j<70;j+=i) {
                    isp[j] =false;
                }
            }
        }
        int q[] = {2, 4, 8, 16, 32, 64, 3, 9, 27, 5, 25, 7, 49};
        REP(i,70) isq[i] = isp[i];
        REP(i,13) isq[q[i]] = true;

        ll rect = X * (X + 1) /2 * Y * (Y + 1) / 2;
        ll total = rect * rect;
        ll prev = total;
        double ans = 0.;
        for (i=2;i<=64;++i) if (isq[i]) {
            ll tmp = func(i);
            ans += (double) (prev - tmp) / total * i;
            prev = tmp;
        }
        return ans;
    }
};

// CUT begin
ifstream data("Undivisors.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> a, double __expected) {
    time_t startClock = clock();
    Undivisors *instance = new Undivisors();
    double __result = instance->getexp(a);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> a;
        from_stream(a);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468127034;
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
        cout << "Undivisors (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
