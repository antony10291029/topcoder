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
const int MAX_BIT = 30;
const ll MAX_VAL = 1ll << 60;
int a[MAX_BIT][3];
class OthersXor {
    public:
    long long minSum(vector<int> x) {
        for (int bit = 0; bit < MAX_BIT; ++bit) {
            a[bit][0] = a[bit][1] = a[bit][2] = 0;
            for (int val : x) {
                if (val < 0) {
                    a[bit][2] += 1;
                    continue;
                }
                if (0 == (val & (1ll << bit))) {
                    a[bit][0] += 1;
                } else {
                    a[bit][1] += 1;
                }
            }
        }
        ll res = 0;
        for (int bit = 0; bit < MAX_BIT; ++bit) {
            ll val = MAX_VAL;
            //sum of one bit is Odd;
            if (a[bit][0] % 2 == 1) {
                val = min(val, (1ll << bit) * a[bit][0]);
            } else if (a[bit][2] > 0) {
                val = min(val, (1ll << bit) * (1 + a[bit][0]));
            }
            //sum of one bit is Even;
            if (a[bit][1] % 2 == 0) {
                val = min(val, (1ll << bit) * a[bit][1]);
            } else if (a[bit][2] > 0) {
                val = min(val, (1ll << bit) * (1 + a[bit][1]));
            }
            if (val == MAX_VAL) {
                return -1;
            }
            res += val;
        }
        return res;
    }
};

// CUT begin
ifstream data("OthersXor.sample");

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

bool do_test(vector<int> x, long long __expected) {
    time_t startClock = clock();
    OthersXor *instance = new OthersXor();
    long long __result = instance->minSum(x);
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
        vector<int> x;
        from_stream(x);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1494812294;
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
        cout << "OthersXor (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
