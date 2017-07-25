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
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int r, c;
int sx, sy;
vector<string> g;
int in(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}
bool check(int dir, int ch, int&len) {
    int cur_x = sx, cur_y = sy;
    len = 0;
    while (true) {
        int nx = cur_x + dx[dir];
        int ny = cur_y + dy[dir];
        if (!in(nx,ny)) break;
        if (g[nx][ny] == ch) return true;
        ++len;
        cur_x = nx;
        cur_y = ny;
    }
    return false;
}
class RobotOnMoon {
    public:
    int longestSafeCommand(vector<string> board) {
        r = board.size();
        c = board[0].size();
        g = board;
        for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) {
            if (g[i][j] == 'S') {
                sx = i, sy = j;
            }
        }
        int res[2] = {0};
        for (int i = 0; i < 4; i++) {
            int len1 = 0;
            if (check(i, '#', len1)) {
                return -1;
            }
            int len2 = 0;
            check((i+2)%4, '#', len2);
            res[i%2] = max(res[i%2], len1 + len2);
        }

        return res[0] + res[1];
    }
};

// CUT begin
ifstream data("RobotOnMoon.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    RobotOnMoon *instance = new RobotOnMoon();
    int __result = instance->longestSafeCommand(board);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500855799;
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
        cout << "RobotOnMoon (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
