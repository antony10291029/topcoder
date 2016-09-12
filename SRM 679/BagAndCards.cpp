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
const int md = 1e9 + 7;
const int N = 1010;
int a[N][N];
int sum[N][N];
inline void add(int &a, int b) {
    a += b;
    if (a >= md) a -= md;
}
inline int mul(int a, int b) {
    return (long long) a * b % md;
}

class BagAndCards {
    public:
    int getHash(int n, int m, int x, int A, int B, int C, string isGood) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = x;
                x = (((long long) x * A + B) ^ C ) % md;
            }
        }
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                sum[j][k] = 0;
                for (int t = 0; t < m; ++t) {
                    if (isGood[k + t] == 'Y') {
                        add(sum[j][k], a[j][t]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int res = 0;
                for (int k = 0; k < m; ++k) {
                    add(res, mul(a[i][k], sum[j][k]));
                }
                ans ^= res;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("BagAndCards.sample");

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

bool do_test(int n, int m, int x, int a, int b, int c, string isGood, int __expected) {
    time_t startClock = clock();
    BagAndCards *instance = new BagAndCards();
    int __result = instance->getHash(n, m, x, a, b, c, isGood);
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
        int m;
        from_stream(m);
        int x;
        from_stream(x);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        string isGood;
        from_stream(isGood);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, x, a, b, c, isGood, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1473642567;
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
        cout << "BagAndCards (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
