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
const int N = 30;
int a[N][N], in[N], vis[N];

class AlphabetOrderDiv1 {
    public:
    string isOrdered(vector<string> words) {
        for (int i = 0; i < N; ++i) {
            in[i] = vis[i] = 0;
            for (int j = 0; j < N; ++j) {
                a[i][j] = 0;
            }
        }
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j+1 < words[i].size(); ++j) {
                int v1 = words[i][j] - 'a', v2 = words[i][j+1] - 'a';
                if (v1 == v2) continue;
                if (a[v1][v2] == 0) {
                    a[v1][v2] = 1;
                    in[v2]++;
                }
            }
        }

        while (true) {
            int c = -1;
            for (int i = 0; i < N; ++i) if (!vis[i] && in[i] == 0) {
                vis[i] = 1;
                c = i;
                break;
            }
            //printf ("\ndebug:c=%d", c);
            if (c == -1) break;
            for (int i = 0; i < N; ++i) if (a[c][i] == 1) {
                --in[i];
            }
        }

        int flag = 0;
        for (int i = 0; i < N; ++i) if (in[i]) flag = 1;

        return flag == 0 ? "Possible" : "Impossible";
    }
};

// CUT begin
ifstream data("AlphabetOrderDiv1.sample");

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

bool do_test(vector<string> words, string __expected) {
    time_t startClock = clock();
    AlphabetOrderDiv1 *instance = new AlphabetOrderDiv1();
    string __result = instance->isOrdered(words);
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
        vector<string> words;
        from_stream(words);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(words, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493296678;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 225 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "AlphabetOrderDiv1 (225 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
