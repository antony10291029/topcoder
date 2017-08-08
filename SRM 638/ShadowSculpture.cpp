#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
const int M = 15;
int a[M][M][M];
int g[M][M][M];
#define REP(i,a) for(int i=0;i<(a);++i)
#define IN(i,a) (0 <= i && i < a)
class ShadowSculpture {
    int n;
    vector<string> XY;
    vector<string> YZ;
    vector<string> ZX;
    bool check (int x, int y, int z) {
        if (!(0 <= x && x < n)) return false;
        if (!(0 <= y && y < n)) return false;
        if (!(0 <= z && z < n)) return false;
        if (XY[x][y] == 'N') return false;
        if (YZ[y][z] == 'N') return false;
        if (ZX[z][x] == 'N') return false;
        return true;
    }
    public:
    string possible(vector<string> _XY, vector<string> _YZ, vector<string> _ZX) {
        XY = _XY;
        YZ = _YZ;
        ZX = _ZX;
        int dx[6] = {1, -1, 0, 0, 0, 0};
        int dy[6] = {0, 0, 1, -1, 0, 0};
        int dz[6] = {0, 0, 0, 0, 1, -1};
        n = XY.size();
        REP(sx, n) REP(sy, n) REP(sz, n) if(check(sx, sy, sz)) {
            //cout << sx << " " << sy << " " << sz << endl;
            queue<int> qx, qy, qz;
            qx.push(sx);
            qy.push(sy);
            qz.push(sz);
            bool used[10][10][10] = {};
            used[sx][sy][sz] = true;
            while(!qx.empty()) {
                int x = qx.front();
                int y = qy.front();
                int z = qz.front();
                qx.pop();
                qy.pop();
                qz.pop();
                REP(r, 6) {
                    int nx = x + dx[r];
                    int ny = y + dy[r];
                    int nz = z + dz[r];
                    if(check(nx, ny, nz) && !used[nx][ny][nz]) {
                        used[nx][ny][nz] = true;
                        qx.push(nx);
                        qy.push(ny);
                        qz.push(nz);
                    }
                }
            }
            //REP(x, n) REP(y, n) REP(z, n) printf("(%d, %d, %d) %d\n", x, y, z, used[x][y][z]);
 
            bool XYB[10][10] = {};
            bool YZB[10][10] = {};
            bool ZXB[10][10] = {};
            REP(x, n) REP(y, n) REP(z, n) if(used[x][y][z]) {
                XYB[x][y] = true;
                YZB[y][z] = true;
                ZXB[z][x] = true;
            }
 
            bool ok = true;
            REP(x, n)REP(y, n) if(XY[x][y] == 'Y' && !XYB[x][y]) ok = false;
            REP(y, n)REP(z, n) if(YZ[y][z] == 'Y' && !YZB[y][z]) ok = false;
            REP(z, n)REP(x, n) if(ZX[z][x] == 'Y' && !ZXB[z][x]) ok = false;
            if(ok) return "Possible";
        }
 
        bool XYB[10][10] = {};
        bool YZB[10][10] = {};
        bool ZXB[10][10] = {};
        bool ok = true;
        REP(x, n)REP(y, n) if(XY[x][y] == 'Y' && !XYB[x][y]) ok = false;
        REP(y, n)REP(z, n) if(YZ[y][z] == 'Y' && !YZB[y][z]) ok = false;
        REP(z, n)REP(x, n) if(ZX[z][x] == 'Y' && !ZXB[z][x]) ok = false;
        if(ok) return "Possible";
        return "Impossible";
    }
};

// CUT begin
ifstream data("ShadowSculpture.sample");

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

bool do_test(vector<string> XY, vector<string> YZ, vector<string> ZX, string __expected) {
    time_t startClock = clock();
    ShadowSculpture *instance = new ShadowSculpture();
    string __result = instance->possible(XY, YZ, ZX);
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
        vector<string> XY;
        from_stream(XY);
        vector<string> YZ;
        from_stream(YZ);
        vector<string> ZX;
        from_stream(ZX);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(XY, YZ, ZX, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502070009;
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
        cout << "ShadowSculpture (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
