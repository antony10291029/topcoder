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
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
void addMod(ll &x, ll y) {
    x = (x + y % mod) % mod;
}
class PowerEquation {
    public:
    int count(int n) {
        //a^b=c^d
        //a=c=1
        ll res = 0;
        addMod(res, (ll) n * n);
        //cout << "res="<< res << endl;
        //a^k
        set<ll>p;
        p.insert(1);
        for (int a = 2; a * a <= n; ++a) {
            //a=c=2..n
            if (p.count(a) > 0) continue;
            int maxx = 0;
            for (ll i = a; i <= n;) {
                if (i <= n) {
                    p.insert(i);
                }
                ++maxx;
                i *= a;
            }
            for (int i = 1; i <= maxx; ++i) {
                for (int j = 1; j <= maxx; ++j) {
                    //a^i a^j
                    //i*x = j*y=> x = j / gcd, y = i / gcd
                    //sz = min(n / x, n / y) => sz = n / max(x, y)
                    int g = gcd(i,j);
                    int x = i / g;
                    int y = j / g;
                    addMod(res, n / max(x,y));
                }
            }
            //cout << "a=" << a << ",maxx=" << maxx << ",res="<< res << endl;
        }
        addMod(res, (n - p.size()) * n);
        return res;
    }
};

// CUT begin
ifstream data("PowerEquation.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    PowerEquation *instance = new PowerEquation();
    int __result = instance->count(n);
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
        next_line();
        int __answer;
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
        int T = time(NULL) - 1493566786;
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
        cout << "PowerEquation (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
