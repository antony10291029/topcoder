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

class FindingFriend {
    public:
    int find(int roomSize, vector<int> leaders, int friendPlace) {
        vector<int> a;
        vector<int> b;
        for (int v : leaders) {
            if (v == friendPlace) return 1;
            else if (v < friendPlace) a.push_back(v);
            else b.push_back(v);
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int all = roomSize * leaders.size();
        cout << "a.size()=" << a.size() << ",b.size()=" << b.size() << endl;
        cout << "all=" << all << endl;
        int res = 0;
        for (int i = 0; i < a.size(); i++) {
            int tmp = (i + 1 + b.size()) * roomSize;
            //cout << "tmp=" << tmp << ",n - a[i] + 1=" << n - a[i] + 1 << endl;
            if (tmp == all - a[i] + 1) return i + 1;
            else res++;
        }
        return res;
    }
};

// CUT begin
ifstream data("FindingFriend.sample");

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

bool do_test(int roomSize, vector<int> leaders, int friendPlace, int __expected) {
    time_t startClock = clock();
    FindingFriend *instance = new FindingFriend();
    int __result = instance->find(roomSize, leaders, friendPlace);
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
        int roomSize;
        from_stream(roomSize);
        vector<int> leaders;
        from_stream(leaders);
        int friendPlace;
        from_stream(friendPlace);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(roomSize, leaders, friendPlace, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493392417;
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
        cout << "FindingFriend (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
