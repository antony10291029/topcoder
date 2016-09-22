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
#define REP(i, a, b) for (int i = (a), end = (b); i < end; ++i)
#define pb push_back
#define mp make_pair
#define x first
#define y second
const int walk[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
const int maxn = 54, maxN = 110;
int n, m;
bool g[maxn + 5][maxn + 5];
int N;
vector<pair<int, int> > all;
int col[maxn + 5][maxn + 5];

inline bool check(int from) {
    static bool need[maxN + 5];
    memset(need, 0, sizeof need);
    REP(i, 0, N) if (i != from) need[i] = 1;

    int sz = N - 1;
    memset(col, -1, sizeof col);
    while (sz > 0) {
        REP(i, 0, N) if (need[i]) {
            bool ban[8] = {0};
            REP(j, 0, 8) {
                int u = all[i].x + walk[j][0], v = all[i].y + walk[j][1];
                if (u < 0 || u >= n || v < 0 || v >= m || g[u][v] || (~col[u][v] && col[u][v] != i)) {
                    ban[j] = 1;
                }
            }
            int cnt[8] = {0};
            int tot = 0;
            REP(j, 0, 8) {
                bool failed = 0;
                REP(k, 0, 5) if (ban[(j + k) & 7]) failed = 1;
                if (failed) continue;
                ++tot;
                REP(k, 0, 5) ++cnt[(j + k) & 7];
            }
            if (!tot) return 0;
            REP(j, 0, 8) if (cnt[j] == tot) {
                int u = all[i].x + walk[j & 7][0], v = all[i].y + walk[j & 7][1];
                if (!~col[u][v]) {
                    col[u][v] = i;
                    REP(k, 0, N) if (k != i && k != from && !need[k] && max(abs(all[k].x - u), abs(all[k].y - v)) <= 1) need[k] = 1, ++sz;
                }
            }
            need[i] = 0;
            --sz;
        }
    }
    return 1;
}


class Puzzle58 {
    public:
    string getAnswer(vector<string> board, vector<int> row, vector<int> col) {
        n = board.size(), m = board[0].size();
        REP(i, 0, n) REP(j, 0, m) g[i][j] = board[i][j] = '#';
        all.clear();
        N =  row.size();
        REP(i, 0, N) all.pb(mp(row[i], col[i]));
        string ret;
        REP(i, 0, N) {
            bool ok[2] = {0};
            bool ban[8] = {0};
            REP(j, 0, i) {
                int u = all[i].x + walk[j][0], v = all[i].y + walk[j][1];
                if (u < 0 || u >= n || v < 0 || v >= m || g[u][v]) ban[j] = 1;
            }
            REP(j, 0, 8) if (!ok[j & 1]) {
                bool failed = 0;
                REP(k, 0, 5) if (ban[(j + k) & 7]) failed = 1;
                if (failed) continue;
                REP(k, 0, 5) {
                    int u = all[i].x + walk[(j + k) & 7][0];
                    int v = all[i].y + walk[(j + k) & 7][1];
                    g[u][v] = 1;
                }
                if (check(i)) ok[j & 1] = 1;
                REP(k, 0, 5) {
                    int u = all[i].x + walk[(j + k) & 7][0];
                    int v = all[i].y + walk[(j + k) & 7][1];
                    g[u][v] = 0;
                }
            }
            if (!ok[0] && !ok[1]) return "Impossible";
            else if (ok[0] && ok[1]) ret += '?';
            else if (ok[0]) ret += 'L';
            else ret += 'C';
        }
        return ret;
    }
};

// CUT begin
ifstream data("Puzzle58.sample");

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

bool do_test(vector<string> board, vector<int> row, vector<int> col, string __expected) {
    time_t startClock = clock();
    Puzzle58 *instance = new Puzzle58();
    string __result = instance->getAnswer(board, row, col);
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
        vector<string> board;
        from_stream(board);
        vector<int> row;
        from_stream(row);
        vector<int> col;
        from_stream(col);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, row, col, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474503565;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Puzzle58 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
