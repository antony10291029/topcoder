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
typedef long long ll;
const int mod = 1e9 + 7;
int add(int x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}
int sub(int x, int y) {
    x -= y;
    if (x < 0) x += mod;
    return x;
}
int mul (ll x, ll y) {
    return 1ll * x * y % mod;
}
int pow(int x, int y) {
    int tmp = 1;
    while (y) {
        if (y&1) tmp = mul(tmp, x);
        x = mul(x, x);
        y >>= 1;
    }
    return tmp;
}
int inv(int x) {
    return pow(x, mod - 2);
}

const int M = 2016;
int d[M][M];
bool used[M];
void calc(int n, int k) {
    memset(d, 0, sizeof(d));
    d[1][0] = 1;
    for (int m = 2; m <= n; ++m) {
        fill(used, used+M, false);
        for (int a = 0; a < m; ++a) {
            if (!used[a]) {
                vector<int> x;
                vector<int> f;
                vector<int> b;
                while (!used[a]) {
                    int nx = (a + k) % m;
                    x.push_back(a);
                    f.push_back(nx);
                    used[a] = true;
                    a = nx;
                    int k = nx - 1;
                    if (k < 0) k += m;
                    if (k == 0) b.push_back(0);
                    else b.push_back(d[m - 1][k % (m - 1)]);
                }
                vector<int> A, B;
                A.push_back(1);
                B.push_back(0);
                for (int i = 0; i < (int) x.size(); ++i) {
                    A.push_back(mul(2, A.back()));
                    B.push_back(sub(mul(2, B.back()), b[i]));
                }
                int alpha = sub(A.back(), 1);
                int beta = B.back();
                int X = mul(sub(0, beta), inv(alpha));
                for (int i = 0; i < (int) x.size(); ++i) {
                    d[m][x[i]] = add(mul(A[i], X), B[i]);
                }
            }
        }
    }
}
class BearCircleGame {
    public:
    int winProbability(int n, int k) {
        calc(n, k);
        return d[n][0];
    }
};

// CUT begin
ifstream data("BearCircleGame.sample");

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

bool do_test(int n, int k, int __expected) {
    time_t startClock = clock();
    BearCircleGame *instance = new BearCircleGame();
    int __result = instance->winProbability(n, k);
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
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469060536;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 800 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BearCircleGame (800 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
