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
typedef long long LL;
#define REP(i,a) for(int i=0;i<a;++i)

class SimilarRatingGraph {
    public:
    double maxLength(vector<int> date, vector<int> rating) {
        int n = date.size();
        double res = 0.0;
        REP(i,n-1) REP(j,n-1) {
            if (j == i) continue;
            LL p = date[j + 1] - date[j];
            LL q = date[i + 1] - date[i];
            double tmp = 0.0;
            for (int len = 1; i + len < n && j + len < n; ++len) {
                int idx1 = i + len;
                int idx2 = j + len;
                LL dx1 = date[idx1] - date[idx1 - 1];
                LL dx2 = date[idx2] - date[idx2 - 1];
                if (dx1 * p != dx2 * q) break;
                LL dy1 = rating[idx1] - rating[idx1 - 1];
                LL dy2 = rating[idx2] - rating[idx2 - 1];
                if (dy1 * p != dy2 * q) break;
                tmp += sqrt(dx1 * dx1 + dy1 * dy1);
                res = max(res, tmp);
            }
        }
        
        return res;
    }
};

// CUT begin
ifstream data("SimilarRatingGraph.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> date, vector<int> rating, double __expected) {
    time_t startClock = clock();
    SimilarRatingGraph *instance = new SimilarRatingGraph();
    double __result = instance->maxLength(date, rating);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> date;
        from_stream(date);
        vector<int> rating;
        from_stream(rating);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(date, rating, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502547027;
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
        cout << "SimilarRatingGraph (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
