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

#define pw(x) (1ll<<(x))
#define pb push_back


using namespace std;

long long f[1000001];

class ClassicProblem {
    public:
    long long maximalValue(vector<int> cnt, vector<int> w, vector<int> v, int limit) {
        for (int i = 0; i < w.size(); i++) for (int j = i + 1; j < w.size(); j++) if (v[i] * 1ll * w[j] < v[j] * 1ll * w[i]) {
            swap(w[i], w[j]);
            swap(v[i], v[j]);
            swap(cnt[i], cnt[j]);
        }
        int mw = 80 * 80 * 80;
        
        int mr = 0;
        for (int i = 0; i < w.size(); i++) {
            int ff = min(cnt[i], 80);
            vector<int> co;
            for (int j = 0; j < 10; j++) if (pw(j) <= ff) {
                co.pb(pw(j));
                ff -= pw(j);
            }

            if (ff > 0) co.pb(ff);
            for (int g = 0; g < co.size(); g++) {
                long long ww = w[i] * 1ll * co[g];
                long long vv = v[i] * 1ll * co[g];

                long long fr = min(mw - ww, (long long) mr);
                for (int j = fr; j >= 0; j--) f[j + ww] = max(f[j + ww], f[j] + vv);
                mr += ww;
            }

        }
        long long ans = 0;
        for (int i = 0; i <= mw; i++) {
            if (i <= limit) {
                int re = limit - i;
                long long val = f[i];
                for (int j = 0; j < w.size(); j++) {
                    int t = max(0, cnt[j] - 80);
                    int h = min(re / w[j], t);

                    val += h * 1ll * v[j];
                    re -= w[j] * 1ll * h;
                }
                ans = max(ans, val);
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("ClassicProblem.sample");

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

bool do_test(vector<int> cnt, vector<int> w, vector<int> v, int limit, long long __expected) {
    time_t startClock = clock();
    ClassicProblem *instance = new ClassicProblem();
    long long __result = instance->maximalValue(cnt, w, v, limit);
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
        vector<int> cnt;
        from_stream(cnt);
        vector<int> w;
        from_stream(w);
        vector<int> v;
        from_stream(v);
        int limit;
        from_stream(limit);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cnt, w, v, limit, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483281913;
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
        cout << "ClassicProblem (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
