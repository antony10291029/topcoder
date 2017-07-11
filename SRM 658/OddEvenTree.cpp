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
const int MX = 55;
int g[MX][MX];
class OddEvenTree {
    public:
    vector<int> getTree(vector<string> x) {
        int n = x.size();
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) g[i][j] = (x[i][j] == 'O');
        vector<int> res;
        res.push_back(-1);
        // two point connect by 0
        for (int i = 0; i < n; ++i) {
            bool existOdd = false;
            for (int j = 0; j < n; ++j) {
                int a = g[0][i];
                int b = g[0][j];
                int c = g[i][j];
                int tmp = a ^ b;
                if (c != tmp) return res;
                if (c == 1) existOdd = true;
            }
            if (!existOdd) return res;
        }
        res.resize(0);
        int odd = -1;
        for (int i = 1; i < n; ++i) if (g[0][i] == 1) odd = i;

        res.push_back(0);
        res.push_back(odd);
        for (int i = 1; i < n; ++i) {
            if (i == odd) continue;
            if (g[0][i] == 0) {
                res.push_back(odd);
                res.push_back(i);
            } else {
                res.push_back(0);
                res.push_back(i);
            }
        }
        
        return res;
    }
};

// CUT begin
ifstream data("OddEvenTree.sample");

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

bool do_test(vector<string> x, vector<int> __expected) {
    time_t startClock = clock();
    OddEvenTree *instance = new OddEvenTree();
    vector<int> __result = instance->getTree(x);
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
        vector<string> x;
        from_stream(x);
        next_line();
        vector<int> __answer;
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
        int T = time(NULL) - 1498437126;
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
        cout << "OddEvenTree (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
