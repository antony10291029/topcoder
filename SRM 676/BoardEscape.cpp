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
#define REP(i,a,b) for(int i = (a); i < b; ++i)

const int M = 256;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
int sx, sy;
char a[60][60];
int f[M][60][60];

int solve(int k, int x, int y) {
    if (k >= M) {
        int c = 1;
        for (;;c++) {
            bool ok = true;
            for (int i = M/2; i + c < M; ++i) if (f[i][x][y] != f[i + c][x][y]) {
                ok = false;
                break;
            }
            if (ok) break;
        }
        k -= ((k - M) / c + 2) * c;
    }
    return f[k][x][y];
}

class BoardEscape {
    public:
    string findWinner(vector<string> s, int k) {
        sx = s.size();
        sy = s[0].length();

        REP(x, 0, sx) REP(y, 0, sy) a[x][y] = s[x][y];
        memset(f, 0, sizeof(f));
        REP(d, 1, M) REP(x, 0, sx) REP(y, 0, sy) if (a[x][y] != '#' && a[x][y] != 'E') {
            bool c[5];
            memset(c, false, sizeof(c));
            REP(p, 0, 4) {
                int x2 = x + dx[p], y2 = y + dy[p];
                if (x2 < 0 || x2 >= sx || y2 < 0 || y2 >= sy || a[x2][y2]=='#') continue;
                if (a[x2][y2] == 'E') c[0] = true;
                else c[f[d - 1][x2][y2]] = true;
            }
            REP(p, 0, 5) if (!c[p]) {
                f[d][x][y] = p;
                break;
            }
        }
        int sg = 0;
        REP(x, 0, sx) REP(y, 0, sy) if (a[x][y] == 'T') sg ^= solve(k, x, y);
        return sg ? "Alice" : "Bob";
    }
};

// CUT begin
ifstream data("BoardEscape.sample");

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

bool do_test(vector<string> s, int k, string __expected) {
    time_t startClock = clock();
    BoardEscape *instance = new BoardEscape();
    string __result = instance->findWinner(s, k);
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
        vector<string> s;
        from_stream(s);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475159204;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoardEscape (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
