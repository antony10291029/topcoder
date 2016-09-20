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
inline int turn(int xa, int ya, int xb, int yb, int xc, int yc) {
    int a = yb - ya;
    int b = xa - xb;
    int c = -a * xa - b * ya;
    int z = a * xc + b * yc + c;
    return z;
}
const int N = 777;
int f[N][N];
class RedAndBluePoints {
    public:
    int find(vector<int> bx, vector<int> by, vector<int> rx, vector<int> ry) {
        int nb = bx.size();
        int nr = rx.size();
        for (int i = 0; i < nb; ++i) {
            for (int j = i + 1; j < nb; ++j) {
                if (by[i] > by[j] || (by[i] == by[j] && bx[i] > by[j])) {
                    swap(bx[i], bx[j]);
                    swap(by[i], by[j]);
                }
            }
        }
        int ans = min(nb, 2);
        for (int st = 0; st < nb; ++st) {
            for (int i = st + 1; i < nb; ++i) {
                for (int j = i + 1; j < nb; ++j) {
                    if (turn(bx[st], by[st], bx[i], by[i], bx[j], by[j]) > 0) {
                        swap(bx[i], bx[j]);
                        swap(by[i], by[j]);
                    }
                }
            }
            for (int i = st; i < nb; ++i) {
                for (int j = i + 1; j < nb; ++j) {
                    f[i][j] = -42424242;
                }
            }
            for (int i = st + 1; i < nb; ++i) {
                f[st][i] = 2;
            }
            for (int i = st; i < nb; ++i) {
                for (int j = i + 1; j < nb; ++j) {
                    if (f[i][j] >= 0) {
                        ans = max(ans, f[i][j]);
                        for (int k = j + 1; k < nb; ++k) {
                            if (turn(bx[i], by[i], bx[j], by[j], bx[k], by[k]) > 0) {
                                continue;
                            }
                            bool ok = true;
                            for (int t = 0; t < nr; ++t) {
                                if (turn(bx[j], by[j], bx[k], by[k], rx[t], ry[t]) < 0) {
                                    if (turn(bx[st], by[st], bx[j], by[j], rx[t], ry[t]) < 0) {
                                        if (turn(bx[k], by[k], bx[st], by[st], rx[t], ry[t]) < 0) {
                                            ok = false;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (!ok) {
                                continue;
                            }
                            int add = 1;
                            for (int t = j + 1; t < k; ++t) {
                                if (turn(bx[j], by[j], bx[k], by[k], bx[t], by[t]) < 0) {
                                    ++add;
                                }
                            }
                            f[j][k] = max(f[j][k], f[i][j] + add);
                        }
                    }
                }
            }
            for (int i = st + 1; i < nb; ++i) {
                for (int j = i + 1; j < nb; ++j) {
                    if (by[i] > by[j] || (by[i] == by[j] && bx[i] > by[j])) {
                        swap(bx[i], bx[j]);
                        swap(by[i], by[j]);
                    }
                }
            }
        }

        return ans;
    }
};

// CUT begin
ifstream data("RedAndBluePoints.sample");

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

bool do_test(vector<int> blueX, vector<int> blueY, vector<int> redX, vector<int> redY, int __expected) {
    time_t startClock = clock();
    RedAndBluePoints *instance = new RedAndBluePoints();
    int __result = instance->find(blueX, blueY, redX, redY);
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
        vector<int> blueX;
        from_stream(blueX);
        vector<int> blueY;
        from_stream(blueY);
        vector<int> redX;
        from_stream(redX);
        vector<int> redY;
        from_stream(redY);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(blueX, blueY, redX, redY, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474333894;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "RedAndBluePoints (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
