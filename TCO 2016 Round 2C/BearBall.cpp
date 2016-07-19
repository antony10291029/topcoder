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
#define REP(i,n) for(int i=0;i<n;++i)
#define SORT(x) sort(x.begin(), x.end())
const double eps = 1e-12;
int cmp(double x) {return x < -eps? -1 : (x>eps? 1 : 0);}
class BearBall {
    public:
    int countThrows(vector<int> x, vector<int> y) {
        int n = x.size();
        int which = 0;
        for (int i = 1; i < n; ++i) {
            if (x[i] < x[which] || (x[i] == x[which] && y[i] < y[which])) {
                which = i;
            }
        }
        vector<double> angle;
        REP(i, n) if (i != which) {
            angle.push_back(atan2(y[i] - y[which], x[i] - x[which]));
        }
        SORT(angle);
        if (cmp(angle[0] - angle.back()) == 0) {
            int ans = 0;
            for (int i = n-1; i >= 1; --i) {
                ans += (1 + i) * i / 2;
            }
            return ans * 2;
        }
        int ans = 0;
        REP(i, n) {
            angle.clear();
            REP(j,n) if (j != i) {
                angle.push_back(atan2(y[j] - y[i], x[j] - x[i]));
            }
            SORT(angle);
            for (int j = 0; j < angle.size(); ) {
                int k = j;
                while (k < angle.size() && cmp(angle[k] - angle[j]) == 0) {
                    ++k;
                }
                ans += 1 + (k - j - 1) * 2;
                j = k;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("BearBall.sample");

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

bool do_test(vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    BearBall *instance = new BearBall();
    int __result = instance->countThrows(x, y);
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
        vector<int> y;
        from_stream(y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468803350;
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
        cout << "BearBall (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
