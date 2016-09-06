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
#define PB push_back
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define RE(i, n) FOR(i, 1, n)
#define SZ(x) (x).size()
#define st first
#define nd second
typedef pair<int, int> PII;
class FleetFunding {
    public:
    int maxShips(int m, vector<int> k, vector<int> a, vector<int> b) {
        
    
    int kl = 0, kp = 1e9, faj = 0;
    vector<vector<int> > wh(m + 2);
    for (int i = 0; i < SZ(a); i++) {
      wh[a[i]].PB(i);
    }
    while (kl <= kp) {
      int aktc = (kl + kp) / 2;
      multiset<PII> secik;
      
      int fail = 0;
      RE (i, m) {
        for (auto p : wh[i]) {
          secik.insert(make_pair(b[p], k[p]));
        }
        int need = aktc;
        while (need > 0) {
          if (secik.empty()) {
            fail = 1;
            break;
          }
          auto p = *secik.begin();
          secik.erase(secik.begin());
          if (p.st < i) {
            continue;
          }
          int got = min(need, p.nd);
          p.nd -= got;
          need -= got;
          if (p.nd) {
            secik.insert(make_pair(p.st, p.nd));
          }
        }
      }
      if (!fail) {
        faj = aktc;
        kl = aktc + 1;
      } else {
        kp = aktc - 1;
      }
    }
    return faj;
    }
};

// CUT begin
ifstream data("FleetFunding.sample");

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

bool do_test(int m, vector<int> k, vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    FleetFunding *instance = new FleetFunding();
    int __result = instance->maxShips(m, k, a, b);
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
        int m;
        from_stream(m);
        vector<int> k;
        from_stream(k);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, k, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1473118069;
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
        cout << "FleetFunding (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
