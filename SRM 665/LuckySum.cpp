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
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define SZ(n) (n.size())
typedef long long ll;
int a[20];
int sz = 0;
ll sum = -1;


void dfs(int idx, int tag, ll digit, int carry, ll base);

void add(int idx, int tag, ll digit, int carry, ll base, int add) {
    ll val = add + carry;
    int new_carry = (val >= 10) ? (val -= 10 ,1) : 0;
    if (idx == 0 && val == 0) {//note[0] beturn '1' and '9'
        return;
    }
    if (a[idx] != -1 && a[idx] != val) {
        return;
    }
    dfs(idx - 1, tag, digit + base * val, new_carry, base * 10);
}

void dfs(int idx, int tag, ll digit, int carry, ll base) {
    if (idx == -1) {
        if (carry == 1) {
            return;
        }
        if (sum == -1 || digit < sum) {
            sum = digit;
        }
        return;
    }
    if (tag == 0) {
        add(idx, tag, digit, carry, base, 0);
        return;
    }
    if (tag == 2) {
        add(idx, tag, digit, carry, base, 8);
        add(idx, tag, digit, carry, base, 11);
        add(idx, tag, digit, carry, base, 14);
    }
    if (tag == 1 && idx != sz - 1) {
        add(idx, tag, digit, carry, base, 4);
        add(idx, tag, digit, carry, base, 7);
    }
    dfs(idx, tag - 1, digit, carry, base);
}




class LuckySum {
    public:
    long long construct(string note) {
        rep(i,SZ(note)) {
            if (note[i] == '?') {
                a[i] = -1;
            } else {
                a[i] = note[i] - '0';
            }
        }
        sum = -1;
        sz = SZ(note);
        dfs(sz - 1, 2, 0, 0, 1);
        return sum;
    }
};

// CUT begin
ifstream data("LuckySum.sample");

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

bool do_test(string note, long long __expected) {
    time_t startClock = clock();
    LuckySum *instance = new LuckySum();
    long long __result = instance->construct(note);
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
        string note;
        from_stream(note);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(note, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1497576936;
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
        cout << "LuckySum (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
