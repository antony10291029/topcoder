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
typedef pair<int,int> PII;
#define fi first
#define se second
PII build_gcd(PII a, PII b) {
    return PII(max(a.fi, b.fi), max(a.se, b.se));
}
PII build_lcm(PII a, PII b) {
    return PII(min(a.fi, b.fi), min(a.se, b.se));
}
PII calc(int n) {
    int k1 = 0, k2 = 0;
    while (n % 2 == 0 && n != 1) n /= 2, ++k1;
    while (n % 3 == 0 && n != 1) n /= 3, ++k2;
    return PII(k1, k2);
}
class LCMGCD {
    public:
    string isPossible(vector<int> x, int t) {
        time_t start = clock();
        PII target = calc(t);
        vector<PII> a;
        for (int tmp : x) {
            a.push_back(calc(tmp));
        }
        for (int it = 0; ; ++it) {
        //    cout << "cnt=" << it << endl;
            vector<PII> v;
            v.push_back(a[0]);
            for (int i = 1; i < a.size(); ++i) {
                vector<PII> nv;
                for (int j = 0; j < v.size(); ++j) {
                    nv.push_back(build_lcm(v[j], a[i]));
                    nv.push_back(build_gcd(v[j], a[i]));
                }
                sort(nv.begin(), nv.end());
                nv.resize(distance(nv.begin(), unique(nv.begin(), nv.end())));
                v=nv;
            }
            //if (binary_search(v.begin(), v.end(), target)) return "Possible";
            vector<PII>::iterator iter = lower_bound(v.begin(), v.end(), target);
            if (iter != v.end() && (*iter == target)) return "Possible";
            int tmp = 63 & it;
            if (tmp == 0 && clock() - start > 0.9 * CLOCKS_PER_SEC) {
               break;
            }
            random_shuffle(a.begin(), a.end());
        }
        return "Impossible";
    }
};

// CUT begin
ifstream data("LCMGCD.sample");

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

bool do_test(vector<int> x, int t, string __expected) {
    time_t startClock = clock();
    LCMGCD *instance = new LCMGCD();
    string __result = instance->isPossible(x, t);
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
        int t;
        from_stream(t);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499492393;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 400 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LCMGCD (400 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
