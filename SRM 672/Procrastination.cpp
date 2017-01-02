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

#define rep(i,a,b) for(int i=a;i<b;i++)

using namespace std;
struct atom{
    int x; long long w;
}x[2000000];
long long A[404], L, R;
int m, len, pd[404];
int compare(atom k1, atom k2) {
    return k1.w < k2.w;
}
class Procrastination {
    public:
    long long findFinalAssignee(long long n) {
        L = max(1ll, n - 200);
        R = n + 200;
        int m = R - L; len = 0l;
        rep(i,0,m+1) {
            long long k1 = L + i;
            for (int j = 2; 1ll * j * j <= k1; j++) {
                if (k1 % j == 0)  {
                    x[++len] = (atom){i, j};
                    if (1ll * j * j != k1) x[++len] = (atom) {i, k1/j};
                }
            }
        }
        sort(x+1, x+1+len, compare);
        memset(pd, 0x00, sizeof pd);
        pd[n-L]=1;
        rep(i, 1, len+1) swap(pd[x[i].x],pd[x[i].x+1]);
        rep(i, 0, m + 1) if (pd[i]) return L + i;


        return 0;
    }
};

// CUT begin
ifstream data("Procrastination.sample");

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

bool do_test(long long n, long long __expected) {
    time_t startClock = clock();
    Procrastination *instance = new Procrastination();
    long long __result = instance->findFinalAssignee(n);
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
        long long n;
        from_stream(n);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483331645;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Procrastination (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
