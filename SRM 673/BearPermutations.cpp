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
#define rep(i,a,b) for(int i=a; i < b; i++)
int md;

void add(int &a, int b) {
    a += b;
    if (a >= md) a -= md;
}

int mul(int a, int b) {
    return (long long) a * b % md;
}

int f[777][777][3];
int C[777][777];


class BearPermutations {
    public:
    int countPermutations(int, int, int);
};


int BearPermutations::countPermutations(int N, int S, int MOD) {
    rep(i,0,N+1) rep(j,0,N+1){
        if (j == 0) C[i][j] = 1;
        else {
            if (i == 0) {
                C[i][j] = 0;
            } else {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
            }
        }
    }
    md = MOD;
    rep(n, 1, N+1) rep(s, 0, S+1) rep(c,0,3){
       int ft = 0;
       rep(pos, 0, n) {
           int addd = 0;
           if (c == 1) addd = pos + 1;
           if (c == 2) addd = n - pos;
           if (addd > s) continue;
           rep(sleft, 0, s-addd+1) {
               int sright = s - addd - sleft;
               if (pos == 0 && sleft > 0) continue;
               if (pos == n - 1 && sright > 0) continue;
               int cur = C[n - 1][pos];
               if (pos > 0) {
                   cur = mul(cur, f[pos][sleft][(pos == n-1) ? 0 : 2]);
               }
               if (pos < n - 1) {
                   cur = mul(cur, f[n - pos - 1][sright][(pos == 0)?0:1]);
               }
               add(ft, cur);
           }
       }
       f[n][s][c] = ft;
    }
    int ans = 0;
    rep(s, 0, S+1) {
        add(ans, f[N][s][0]);
    }
    return ans;
}



// CUT begin
ifstream data("BearPermutations.sample");

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

bool do_test(int N, int S, int MOD, int __expected) {
    time_t startClock = clock();
    BearPermutations *instance = new BearPermutations();
    int __result = instance->countPermutations(N, S, MOD);
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
        int N;
        from_stream(N);
        int S;
        from_stream(S);
        int MOD;
        from_stream(MOD);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, S, MOD, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483328670;
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
        cout << "BearPermutations (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
