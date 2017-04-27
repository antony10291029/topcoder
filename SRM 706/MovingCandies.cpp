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
const int N = 25;
int a[N][N];
struct node{
    int x, y;
    int deep;
    int cost;
    node(){}
    node(int _x, int _y, int _deep, int _cost): x(_x), y(_y), deep(_deep), cost(_cost) {}
}st[10000001];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int C[N][N][N*N];
const int inf = N * N;
class MovingCandies {
    public:
    int minMoved(vector<string> t) {
        int r = t.size(), c = t[0].size();
        int total = 0;
        for (int i = 0; i < t.size(); ++i) {
            for (int j = 0; j < t[i].size(); ++j) {
                a[i][j] = t[i][j] == '.';
                total += a[i][j] == 0;
                for (int k = 0; k < r * c; k++) C[i][j][k] = inf;
            }
        }
        int front = 0, tail = 0;
        st[front++] = node(0, 0, 1, a[0][0]);
        C[0][0][1] = a[0][0];

        while (front > tail) {
            node cur = st[tail++];
            for (int dir = 0; dir < 4; dir++) {
                node nxt = node(cur.x + dx[dir], cur.y + dy[dir], cur.deep + 1, cur.cost + a[cur.x + dx[dir]][cur.y + dy[dir]]);
                if (nxt.x >= 0 && nxt.x < r && nxt.y >= 0 && nxt.y < c && nxt.deep <= total && nxt.cost < C[nxt.x][nxt.y][nxt.deep]) {
                    C[nxt.x][nxt.y][nxt.deep] = nxt.cost;
                    st[front++] = nxt;
                }

            }
        }

        int res = inf;
        for (int i = 0; i <= total; ++i) res = min(res, C[r-1][c-1][i]);

        return res == inf ? -1:res;
    }
};

// CUT begin
ifstream data("MovingCandies.sample");

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

bool do_test(vector<string> t, int __expected) {
    time_t startClock = clock();
    MovingCandies *instance = new MovingCandies();
    int __result = instance->minMoved(t);
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
        vector<string> t;
        from_stream(t);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493291752;
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
        cout << "MovingCandies (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
