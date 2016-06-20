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
#include <queue>

using namespace std;

int cnts[27];
class ColorfulGarden {
    public:
    vector<string> rearrange(vector<string> garden) {
        vector<string> ret;
        memset(cnts, 0, sizeof(cnts));
        int n = garden[0].size();
        for (int i = 0; i < n; ++i) {
            ++cnts[garden[1][i] - 'a'];
            ++cnts[garden[0][i] - 'a'];
        }
        priority_queue<pair<int,int> > PQ;
        for (int i = 0; i < 26; ++i) {
            if (cnts[i] > n) return ret;
            else PQ.push(make_pair(cnts[i], i+'a'));
        }
        ret.push_back("");
        ret.push_back("");
        for (int i = 0; i < n; ++i) {
            pair<int,int> f = PQ.top();
            PQ.pop();
            pair<int,int> g = PQ.top();
            PQ.pop();
            if (i == 0 || (ret[0][ret[0].length() - 1] != f.second && ret[1][ret[1].length() - 1] != g.second)) {
                ret[0] += char(f.second);
                ret[1] += char(g.second);
            } else {
                ret[0] += char(g.second);
                ret[1] += char(f.second);
            }
            PQ.push(make_pair(f.first - 1, f.second));
            PQ.push(make_pair(g.first - 1, g.second));
        }
        return ret;
    }
};

// CUT begin
ifstream data("ColorfulGarden.sample");

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

bool do_test(vector<string> garden, vector<string> __expected) {
    time_t startClock = clock();
    ColorfulGarden *instance = new ColorfulGarden();
    vector<string> __result = instance->rearrange(garden);
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
        vector<string> garden;
        from_stream(garden);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(garden, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1466474141;
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
        cout << "ColorfulGarden (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
