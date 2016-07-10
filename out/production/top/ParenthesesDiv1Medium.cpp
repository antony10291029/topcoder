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
#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++) 
const int INF = 1<<29;
int N;
bool reach[2010][2010];
int gL[2010], gR[2010];
bool used[2010];
int dp[2010][2010];

int func(string s) {
    int N = s.length();
    int i,j;

    REP(i,N+1)REP(j,N+1)dp[i][j]=INF;
    dp[0][0]=0;

    REP(i,N)REP(j,i+1){
        int cost = ((s[i]=='(')?0:1);
        dp[i+1][j+1]=min(dp[i+1][j+1], dp[i][j] + cost);
        cost = 1 - cost;
        if (j > 0) {
            dp[i+1][j-1] = min(dp[i+1][j-1], dp[i][j] + cost);
        }
    }
    return dp[N][0];
}

class ParenthesesDiv1Medium {
    public:
    int minSwaps(string s, vector<int> L, vector<int> R) {
        int i,j;
        int N = s.length();
        int cnt1 = 0, cnt2 = 0;
        REP(i,N) {
            if (s[i] == '(') {
                ++cnt1;
            } else {
                ++cnt2;
            }
        }

        REP(i, N+1) gL[i] = gR[i] = i;
        REP(i, L.size()) {
            R[i]++;
            gR[L[i]] = max(gR[L[i]], R[i]);
            gL[R[i]] = min(gL[R[i]], L[i]);
        }

        int x;
        REP(x, N+1) {
            int ansL = gL[x], ansR = gR[x];
            int usedL = x, usedR = x;
            while (1) {
                if (ansL < usedL) {
                    ansL = min(ansL, gL[usedL - 1]);
                    ansR = max(ansR, gR[usedL - 1]);
                    --usedL;
                } else if (ansR > usedR) {
                    ansL = min(ansL, gL[usedR + 1]);
                    ansR = max(ansR, gR[usedR + 1]);
                    ++usedR;
                } else {
                    break;
                }
            }
            for (int i = ansL; i <=ansR; ++i) reach[x][i] = true;
        }
        vector<pair<int, pair<int, int> > > v;//len, L, R
        REP(i, N+1) {
            for(j=i+1;j<=N;++j) {
                if(reach[i][j] && reach[j][i])
                    break;
            }
            if (j <= N) v.push_back(make_pair(j-i,make_pair(i,j)));
        }
        sort(v.begin(), v.end());
        int ans = 0;
        REP(i, v.size()){
            int l = v[i].second.first;
            int r = v[i].second.second;
            string t;
            for (j=l;j<r;++j)if(!used[j]){
                used[j]=true;
                t += s[j];
            }
            if(t.length() % 2 != 0)return -1;
            ans += func(t);
        }
        int balance = 0;
        REP(i,N) if(used[i]) balance += ((s[i] == '(')?1:-1);
        (ans += abs(balance) / 2)/=2;
        int used_cnt = 0;
        REP(i,N)if(used[i])used_cnt++;
        if(min(cnt1,cnt2)*2 <used_cnt)return -1;
        return ans;
    }
};

// CUT begin
ifstream data("ParenthesesDiv1Medium.sample");

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

bool do_test(string s, vector<int> L, vector<int> R, int __expected) {
    time_t startClock = clock();
    ParenthesesDiv1Medium *instance = new ParenthesesDiv1Medium();
    int __result = instance->minSwaps(s, L, R);
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
        vector<int> L;
        from_stream(L);
        vector<int> R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1466236951;
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
        cout << "ParenthesesDiv1Medium (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
