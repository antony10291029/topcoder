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

class Sunnygraphs {
    public:
    long long count(vector<int> a) {
        int f1[505], f2[505];
        int n = a.size();
        for (int i = 0; i < n + 10; ++i) f1[i] = 0, f2[i] = 0;
        int p = 0;
        for (int i = 0; i < n + 10; ++i) {
            f1[p] = 1;
            p = a[p];
        }
        p = 1;
        for (int i = 0; i < n + 10; ++i) {
            f2[p] = 1;
            p = a[p];
        }
        int cnt[2][2];
        cnt[0][0] = cnt[0][1] = cnt[1][0] = cnt[1][1] = 0;
        for (int i = 0; i < n; ++i) {
            cnt[f1[i]][f2[i]]++;
        }
        long long one = 1LL;
        long long ans = one << n;
        ans -= ((one << cnt[0][1]) - 1) * (one << cnt[0][0]);
        ans -= ((one << cnt[1][0]) - 1) * (one << cnt[0][0]);
        if (cnt[1][1] == 0) {
            ans -= (one << (n - cnt[0][1] -cnt[1][0]));
        }
        return ans;
        return 0;
    }
};

// CUT begin
ifstream data("Sunnygraphs.sample");

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

bool do_test(vector<int> a, long long __expected) {
    time_t startClock = clock();
    Sunnygraphs *instance = new Sunnygraphs();
    long long __result = instance->count(a);
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
        vector<int> a;
        from_stream(a);
        next_line();
        long long __answer;
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
        int T = time(NULL) - 1466943132;
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
        cout << "Sunnygraphs (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
