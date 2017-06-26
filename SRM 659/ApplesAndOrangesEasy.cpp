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
const int MX = 2005;
#define clr(x) memset(x, 0, sizeof(x))
int f[MX*4], a[MX];
void add(int idx, int val) {
    ++idx;
    for (int i = idx; i < MX; i += i&(-i)) f[i] += val;
}
int getValue(int idx) {
    ++idx;
    if (idx <= 0) return 0;
    int sum = 0;
    for (int i = idx; i > 0; i -= i&(-i)) sum += f[i];
    return sum;
}

class ApplesAndOrangesEasy {
    public:
    int maximumApples(int N, int K, vector<int> info) {
        clr(f);clr(a);
        for (int x : info) {
            add(x - 1, 1);
            a[x-1] = 1;
        }
        for (int i = 0; i < N; ++i) {
            if (a[i]) continue;
            add(i, 1), a[i] = 1;
            int ok = true;
            for (int j = i; j < i + K; j++) {
                int tmp = getValue(j);
                if (j - K >= 0) tmp -= getValue(j - K);
                if (tmp > K / 2) {
                    ok = false;
                    break;
                }
            }
            if (!ok) add(i, -1), a[i] = 0;
        }
        int res = 0;
        for (int i = 0; i < N; ++i) res += a[i];
        return res;
    }
};

// CUT begin
ifstream data("ApplesAndOrangesEasy.sample");

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

bool do_test(int N, int K, vector<int> info, int __expected) {
    time_t startClock = clock();
    ApplesAndOrangesEasy *instance = new ApplesAndOrangesEasy();
    int __result = instance->maximumApples(N, K, info);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        vector<int> info;
        from_stream(info);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, info, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498397820;
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
        cout << "ApplesAndOrangesEasy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
