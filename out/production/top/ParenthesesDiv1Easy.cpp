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
#define FOR(i, a, b) for(int i = (a), _ed = (b); i < _ed; ++i)
#define FORD(i, a, b) for(int i = (a), _be = (b); i >= _be; --i)
#define pb push_back
#define VI vector<int>
int a[1005];
int sum[1005];
class ParenthesesDiv1Easy {
    public:
    vector<int> correct(string s) {
    	int n = s.length();
    	VI ans; ans.pb(-1);
    	if (n % 2 != 0) return ans;
    	ans.clear();
    	FOR(i, 0, n) {
    		if (s[i] == '(') a[i] = 1;
    		else a[i] = -1;
    	}
    	sum[0] = a[0];
    	FOR(i, 1, n) sum[i] = sum[i - 1] + a[i];
    	int mini = 0;
    	int dla = -1;
    	FOR(i,0,n) {
    		if (sum[i] < mini) {
    			mini = sum[i];
    			dla = i;
    		}
    	}
    	if (mini < 0) {
    		ans.pb(0);
    		ans.pb(dla);
    		for (int i = 0; i < dla - i; ++i) {
    			swap(a[i], a[dla - i]);
    		}
    		FOR(i,0,dla+1)a[i] = -a[i];
    		sum[0] = a[0];
    		FOR(i,1,n) sum[i] = sum[i-1] + a[i];
    	}
    	if (sum[n-1]==0)return ans;
    	FORD(j, n-1, 0) {
    		if (sum[j] == sum[n-1] / 2) {
    			ans.pb(j+1);
    			ans.pb(n-1);
    			break;
    		}
    	}
        return ans;
    }
};

// CUT begin
ifstream data("ParenthesesDiv1Easy.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(string s, vector<int> __expected) {
    time_t startClock = clock();
    ParenthesesDiv1Easy *instance = new ParenthesesDiv1Easy();
    vector<int> __result = instance->correct(s);
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
        string s;
        from_stream(s);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1466231755;
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
        cout << "ParenthesesDiv1Easy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
