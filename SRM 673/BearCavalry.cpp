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


#define rep(i,a,b) for(int i = a; i < b; i++)
using namespace std;
typedef vector<int> VI;
const int md = 1000000007;
class BearCavalry {
    public:
    int countAssignments(vector<int> a, vector<int> b) {
        int n = a.size();
        int ans = 0;
        rep(to, 0, n){
            int str = a[0] * b[to];
            vector<int> c, d;
            rep(i, 1, n) c.push_back(a[i]);
            rep(i, 0, n) if (i != to) d.push_back(b[i]);
            VI cnt(n - 1, 0);
            rep(i, 0, n-1) rep(j, 0, n-1) if (c[i] * d[j] < str) cnt[i]++;
            sort(cnt.begin(), cnt.end());
            int cur = 1;
            rep(i,0,n-1){
                int by = cnt[i] - i;
                if (by <= 0) {
                    cur = 0;
                    break;
                }
                cur = (long long) cur * by % md;
            }
            ans = (ans + cur) % md;
        }
        return ans;
    }
};

// CUT begin
ifstream data("BearCavalry.sample");

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

bool do_test(vector<int> warriors, vector<int> horses, int __expected) {
    time_t startClock = clock();
    BearCavalry *instance = new BearCavalry();
    int __result = instance->countAssignments(warriors, horses);
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
        vector<int> warriors;
        from_stream(warriors);
        vector<int> horses;
        from_stream(horses);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(warriors, horses, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483323595;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BearCavalry (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
