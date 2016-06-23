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
typedef long long ll;
typedef long double ld;
const int MAXN = 210;
const ld PI = acos(-1.0);
#define X first
#define Y second

int N;
int ord[MAXN];
pair <double, double> pt[MAXN];
void rotate(int k) {
    double x = pt[k].X, y = pt[k].Y;
    ld angle = PI / 5000;
    ld s = sin(angle), c = cos(angle);
    double xnew = x * c - y * s;
    double ynew = x * s + y * c;
    pt[k] = make_pair(xnew, ynew);
}

ld sq(ld a) {
    return a *a;
}

ld dist(int a, int b) {
    return sqrt (sq (pt[a].X - pt[b].X) + sq (pt[a].Y - pt[b].Y));
}

ld cross (int a, int b, int c) { // b - a cross c - a
    return (pt[b].X - pt[a].X) * (pt[c].Y - pt[a].Y) - (pt[c].X - pt[a].X) * (pt[b].Y - pt[a].Y);
}

bool bad(int a, int b, int c, int d) {
    if (cross(a, b, c) * cross(a, b, d) >= 0) return false;
    if (cross(c, d, a) * cross(c, d, b) >= 0) return false;
    return true;
}




class ZeroPointSixThreeSix {
    public:
    vector<int> replan(vector<int> x, vector<int> y, vector<int> match) {
        N = x.size();
        for (int i = 0; i < N; ++i) {
            pt[i] = make_pair(x[i], y[i]);
        }
        ld tdist = 0;
        for (int i = 0; i < N; ++i) {
            tdist += dist (i, match[i]);
        }
        for (int i = 0; i < 5000; ++i) {
            ld cdist = 0.0;
            for (int j = 0; j < N; ++j) {
                cdist += abs (pt[j].X - pt[match[j]].X);
            }
            if (cdist / tdist > 0.63601) {
                break;
            }
            for (int j = 0; j < N; ++j) {
                rotate(j);
            }
        }
        for (int i = 0; i < N; ++i) {
            if (pt[i].X < pt[match[i]].X) {
                ord[i] = 0;
                ord[match[i]] = 1;
            } else {
                ord[i] = 1;
                ord[match[i]] = 0;
            }
        }
        while(true) {
            bool found = false;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    if (ord[i] && ord[j]) {
                        if (bad (i, match[i], j, match[j])) {
                            found = true;
                            int a = i, b = match[i], c = j, d = match[j];
                            match[a] = d;
                            match[d] = a;
                            match[b] = c;
                            match[c] = b;
                        } 
                    }
                }
            }
            if (!found) break;
        }
        return match;
    }
};

// CUT begin
ifstream data("ZeroPointSixThreeSix.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> match, vector<int> __expected) {
    time_t startClock = clock();
    ZeroPointSixThreeSix *instance = new ZeroPointSixThreeSix();
    vector<int> __result = instance->replan(x, y, match);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> match;
        from_stream(match);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, match, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1466578116;
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
        cout << "ZeroPointSixThreeSix (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
