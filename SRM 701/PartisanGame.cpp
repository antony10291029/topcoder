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
const int N = 10010;
bool dp[N+10][2];
class PartisanGame {
    public:
    string getWinner(int n, vector<int> a, vector<int> b) {
        memset(dp, 0, sizeof(dp));
        for (int i=1; i<=N; i++) {
            dp[i][0] = false;
            for (int j = 0; j < a.size(); ++j) {
                int x = i - a[j];
                if (x >= 0 && !dp[x][1]) dp[i][0] = true;
            }
            dp[i][1] = 0;
            for (int j = 0; j < b.size(); ++j) {
                int x = i - b[j];
                if (x >= 0 && !dp[x][0]) dp[i][1] = true;
            }
        }
        if (n <= N) {
            return dp[n][0]?"Alice":"Bob";
        }
        int cyc = 1;
        for (;;cyc++) {
            int flag = 0;
            for (int i = 0; i < 5; i++) {
                int x = N - i;
                int y = N - i - cyc;
                if (dp[x][0] != dp[y][0] || dp[x][1] != dp[y][1]) flag = 1;
            }
            if (!flag) {
                n = (N - cyc) + (n - N) % cyc;
                break;
            }
        }
        return dp[n][0]?"Alice":"Bob";
    }
};

// CUT begin
ifstream data("PartisanGame.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, string __expected) {
    time_t startClock = clock();
    PartisanGame *instance = new PartisanGame();
    string __result = instance->getWinner(n, a, b);
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
        int n;
        from_stream(n);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493392394;
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
        cout << "PartisanGame (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
