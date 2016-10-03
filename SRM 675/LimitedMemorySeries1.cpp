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
const int N = 250010;
const int BLOCK = 4001;

int a[N];
int id[123];

class LimitedMemorySeries1 {
    public:
    long long getSum(int n, int x0, int aa, int bb, vector<int> query) {
        for (int i = 0; i < N; ++i) {
            a[i] = 0;
        }
        int x = x0;
        for (int i = 0; i < n; ++i) {
            a[x / BLOCK]++;
            x = ((long long) x * aa + bb) % md;
        }
        int qcnt = query.size();
        for (int i = 0; i < qcnt; ++i) {
            int total = 0;
            id[i] = -1;
            for (int j = 0; j < N; ++j) {
                total += a[j];
                if (total > query[i]) {
                    query[i] -= (total - a[j]);
                    id[i] = j;
                    break;
                }
            }
        }
        long long ans = 0;
        for (int rot = 0; rot < 2; ++rot) {
            int from, to;
            if (rot == 0) {
                from = 0;
                to = qcnt / 2;
            } else {
                from = qcnt / 2;
                to = qcnt;
            }
            for (int i = 0; i < (to - from) * BLOCK; ++i) {
                a[i] = 0;
            }
            int x = x0;
            for (int i = 0; i < n; ++i) {
                int at = x / BLOCK;
                int pos = x % BLOCK;
                for (int j = from; j < to; ++j) {
                    if (id[j] == at) {
                        a[(j - from) * BLOCK + pos]++;
                    }
                }
                x = ((long long) x * aa + bb) % md;
            }
            for (int j = from; j < to; ++j) {
                int total = 0;
                for (int i = 0; i < BLOCK; ++i) {
                    total += a[(j - from) * BLOCK + i];
                    if (total > query[j]) {
                        ans += id[j] * BLOCK + i;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("LimitedMemorySeries1.sample");

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

bool do_test(int n, int x0, int a, int b, vector<int> query, long long __expected) {
    time_t startClock = clock();
    LimitedMemorySeries1 *instance = new LimitedMemorySeries1();
    long long __result = instance->getSum(n, x0, a, b, query);
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
        int x0;
        from_stream(x0);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        vector<int> query;
        from_stream(query);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, x0, a, b, query, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475717494;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LimitedMemorySeries1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
