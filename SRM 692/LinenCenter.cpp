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
const int mod = 1e9 + 9;
int P[111],X[111][26],D[1111][111];
int V[1111],U[1111],T[1111];
void add (int &a, int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
}

class LinenCenter {
    public:
    int countStrings(string S, int N, int K) {
        int L = S.length();
        S = " " + S;
        int k = 0; P[1] = 0;
        for (int i = 2; i <= L; ++i) {
            while (k > 0 && S[k+1] != S[i]) {
                k = P[k];
            }
            if (S[k+1] == S[i]) ++k;
            P[i] = k;
        }
        for (int i = 0; i < L; ++i) {
            for (int c = 0; c < 26; ++c) {
                int k = i;
                while (k > 0 && S[k+1] != c + 'a') k = P[k];
                if (S[k+1] == c + 'a') ++k;
                X[i][c] = k;
            }
        }
        for (int i = 0; i <= L; ++i) for (int j = 0; j <= N; ++j) D[j][i] = 0;
        D[0][P[L]] = 1;
        for (int j = 1; j <= N; ++j) {
            for (int i = 0; i < L; ++i) for (int c = 0; c < 26; ++c) {
                add(D[j][X[i][c]], D[j-1][i]);
            }
        }

        for (int j = 0; j <= N; ++j) {
            V[j] = U[j] = 0;
            for (int i = 0; i < L; ++i) add(V[j], D[j][i]);
            V[j] %= mod;
        }
        U[0] = 1;

        while (K) {
            if (K & 1) {
                for (int j = 0; j <= N; ++j) T[j] = 0;
                for (int i = 0; i <= N; ++i) for(int j = 0; i + j <= N; ++j) T[i+j] = (T[i+j] + (long long)V[i] * U[j]) % mod;
                for (int j = 0; j <= N; ++j) U[j] = T[j];
            }
            for (int j = 0; j <= N; ++j) T[j] = 0;
            for (int i = 0; i <= N; ++i) for (int j = 0; i + j <= N; ++j) T[i + j] = (T[i + j] + (long long)V[i] * V[j]) % mod;
            for (int j = 0; j <= N; ++j) V[j] = T[j];
            K /= 2;
        }
        for (int i = 0; i <= L; ++i) for (int j = 0; j <= N; ++j) D[j][i] = 0;
        D[0][0] = 1;
        for (int j = 1; j <= N; ++j) {
            for (int i = 0; i < L; ++i) for (int c = 0; c < 26; ++c) {
                add(D[j][X[i][c]], D[j-1][i]);
            }
        }

        for (int j = 0; j <= N; ++j) {
            V[j] = 0;
            for (int i = 0; i < L; ++i) add(V[j], D[j][i]);
        }
        for (int j = 0; j <= N; ++j) T[j] = 0;
        for (int i = 0; i <= N; ++i) for (int j = 0; i + j <= N; ++j) T[i + j] = (T[i + j] + (long long)V[i] * U[j]) % mod;
        for (int j = 0; j <= N; ++j) U[j] = T[j];
        int ans = 0;
        for (int j = 0; j <= N; ++j) add(ans, U[j]);
        return ans;
    }
};

// CUT begin
ifstream data("LinenCenter.sample");

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

bool do_test(string S, int N, int K, int __expected) {
    time_t startClock = clock();
    LinenCenter *instance = new LinenCenter();
    int __result = instance->countStrings(S, N, K);
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
        string S;
        from_stream(S);
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467202516;
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
        cout << "LinenCenter (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
