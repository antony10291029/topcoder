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

class TreeAndPathLength3 {
    public:
    void solve(int s, int &a, int &b, int &mi) {
        for (int i = 1; i <= 100; ++i) for (int j = 1; j <= 100; ++j) {
            int t = i * j + j * (j - 1);
            if (t <= s && s - t < mi) {
                mi = s - t;
                a = i;
                b = j;
            }
        }
    }
    vector<int> construct(int s) {
        int a = 0, b = 0, mi = 1e9;
        solve(s, a, b, mi);
        vector<int> ans;
        for (int i = 0; i < a; ++i) {
            ans.push_back(0);
            ans.push_back(1 + i);
        }
        int last = a;
        for (int i = 0; i < b; ++i) {
            last++;
            ans.push_back(0);
            ans.push_back(last);

            last++;
            ans.push_back(last - 1);
            ans.push_back(last);
        }

        for (int i = 0; i < mi; ++i) {
            last++;
            ans.push_back(last - 1);
            ans.push_back(last);
        }
        return ans;
    }
};

// CUT begin
ifstream data("TreeAndPathLength3.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int s, vector<int> __expected) {
    time_t startClock = clock();
    TreeAndPathLength3 *instance = new TreeAndPathLength3();
    vector<int> __result = instance->construct(s);
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
        int s;
        from_stream(s);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475393285;
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
        cout << "TreeAndPathLength3 (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
