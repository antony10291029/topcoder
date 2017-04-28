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
const int N = 55;
vector<int> v[N];
class TreeDistanceConstruction {
    public:
    vector<int> construct(vector<int> d) {
        for (int i = 0; i < N; ++i) v[i].clear();
        int mx = d[0];
        int mi = d[0];
        for (int i = 0; i < d.size(); ++i) {
            v[d[i]].push_back(i);
            if (d[i] > mx) mx = d[i];
            if (d[i] < mi) mi = d[i];
        }
        vector<int> longestL;
        int canMin = mx;
        for (int i = 0; i <= mx; i++) {
            int tmp = max(i, mx - i);
            if (v[tmp].size() == 0) {
                return vector<int>();
            }
            canMin = min(canMin, tmp);
            longestL.push_back(v[tmp].back());
            v[tmp].pop_back();
        }
        /*if (mi < canMin) {
            return vector<int>();
        }*/
        vector<int> res;
        for (int i = 0; i + 1 < longestL.size(); i++) {
            res.push_back(longestL[i]);
            res.push_back(longestL[i+1]);
        }
        for (int i = 1; i <= mx; i++) {
            for (int j : v[i]) {
                if ((mx+1) / 2 + 1 > i) {
                    return vector<int>();
                }
                res.push_back(j);
                res.push_back(longestL[i - 1]);
            }
        }


        return res;
    }
};

// CUT begin
ifstream data("TreeDistanceConstruction.sample");

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

bool do_test(vector<int> d, vector<int> __expected) {
    time_t startClock = clock();
    TreeDistanceConstruction *instance = new TreeDistanceConstruction();
    vector<int> __result = instance->construct(d);
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
        vector<int> d;
        from_stream(d);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493305427;
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
        cout << "TreeDistanceConstruction (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
