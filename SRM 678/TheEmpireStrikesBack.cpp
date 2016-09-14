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

struct point_t {
    long long x, y;
    bool operator < (const point_t &other) const {
        if (other.x != x) return x < other.x;
        return y < other.y;
    }
};
const int MOD = 1e9 + 7;
class TheEmpireStrikesBack {
    public:
    int find(int AX, int BX, int CX, int AY, int BY, int CY, int N, int M) {
        vector<point_t> P(N);
        P[0].x = AX;
        for (int i = 1; i < N; ++i) P[i].x = ((P[i - 1].x * BX) + CX) % MOD;
        P[0].y = AY;
        for (int i = 1; i < N; ++i) P[i].y = ((P[i - 1].y * BY) + CY) % MOD;
        sort(P.begin(), P.end());
        vector<point_t> Q;
        for (int i = 0; i < N; ++i) {
            while (!Q.empty() && Q.back().y <= P[i].y) Q.pop_back();
            if (Q.empty() || Q.back().x < P[i].x) {
                Q.push_back(P[i]);
            }
        }
        long long low = 0, high = MOD;
        int ans = -1;
        while (low <= high) {
            long long mid = (low + high) >> 1;
            int cnt = 0;
            long long needY = -1;
            long long coverX = -1;
            point_t last;
            long long T = mid;
            for (int i = 0; i < Q.size(); ++i) {
                if (Q[i].x > coverX) {
                    needY = max(needY, Q[i].y);
                    if (needY > Q[i].y + T) {
                        coverX = last.x + T;
                        --i;
                        needY = -1;
                        ++cnt;
                        continue;
                    }
                }
                last = Q[i];
            }
            if (needY >= 0) {
                ++cnt;
            }
            if (cnt <= M) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("TheEmpireStrikesBack.sample");

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

bool do_test(int AX, int BX, int CX, int AY, int BY, int CY, int N, int M, int __expected) {
    time_t startClock = clock();
    TheEmpireStrikesBack *instance = new TheEmpireStrikesBack();
    int __result = instance->find(AX, BX, CX, AY, BY, CY, N, M);
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
        int AX;
        from_stream(AX);
        int BX;
        from_stream(BX);
        int CX;
        from_stream(CX);
        int AY;
        from_stream(AY);
        int BY;
        from_stream(BY);
        int CY;
        from_stream(CY);
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(AX, BX, CX, AY, BY, CY, N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1472864667;
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
        cout << "TheEmpireStrikesBack (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
