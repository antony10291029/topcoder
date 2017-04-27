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

int a[1002];
int x[1002], y[1002],z[1002];
class MazeConstruct {
    public:
    vector<string> construct(int k) {
        for (int i = 2; i <= 50; i++) {
            int t = (i + 1) * 2;
            for (int j = 0;j <= 24; j++) {
                if (i + t*j > 1001) break;
                if (0 == a[i + t*j]) {
                    a[i + t*j] = 1;
                    x[i + t*j] = i;
                    y[i + t*j] = j;
                    z[i + t*j] = 0;
                } else if (j < y[i + t*j]) {
                    x[i + t*j] = i;
                    y[i + t*j] = j;
                    z[i + t*j] = 0;
                }
            }
        }
        for (int i = 0; i <= 1001; i++) {
            if (a[i] == 0) {
                x[i] = x[i - 1];
                y[i] = y[i - 1];
                z[i] = z[i - 1] + 1;
            }
        }
        /*for (int i = 0; i <= 1001; i ++) {
            printf("\n%d:%d,", i, a[i]);
            if (a[i] == 1) printf("x=%d,y=%d,z=%d", x[i], y[i],z[i]);
            if (a[i] == 0) printf("x=%d,y=%d,z=%d", x[i], y[i],z[i]);
        }
        printf("\n");*/
        vector<string>res;
        if (k == 1) {
            res.push_back(string(1, '.'));
            return res;
        }
        ++k;
        res.push_back(string(x[k], '.'));
        for (int i = 0; i < y[k]; ++i) {
            res.push_back(string(x[k] - 1, '#') + string(1, '.'));
            res.push_back(string(x[k], '.'));
            res.push_back(string(1, '.') + string(x[k] - 1, '#'));
            res.push_back(string(x[k], '.'));
        }
        for (int i = 0; i < z[k]; ++i) {
            res.push_back(string(x[k] - 1, '#') + string(1, '.'));
        }
        return res;
    }
};

// CUT begin
ifstream data("MazeConstruct.sample");

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

bool do_test(int k, vector<string> __expected) {
    time_t startClock = clock();
    MazeConstruct *instance = new MazeConstruct();
    vector<string> __result = instance->construct(k);
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
        int k;
        from_stream(k);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493216920;
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
        cout << "MazeConstruct (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
