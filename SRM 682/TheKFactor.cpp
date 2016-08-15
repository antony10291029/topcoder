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
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;++i)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;--i)
typedef long long LL;
typedef double db;
const int N = 905;
int n,m;
double val[N];
double a[N][N];
double b[N];
int node[N];
double c[N];
int cnt = 0;
double rotate(int l, int e) {
    rep(i,1,cnt)if(i^e)a[l][i]/=a[l][e];
    b[l]/=a[l][e];a[l][e]=1/a[l][e];
    rep(i,1,m)if(i!=l && fabs(a[i][e])>0){
        b[i]-=b[l]*a[i][e];
        rep(j,1,cnt)if(j^e) a[i][j] -= a[i][e]*a[l][j];
        a[i][e]=-a[i][e]*a[l][e];
    }
    double re=b[l]*c[e];
    rep(i,1,cnt)if(i^e)c[i]-=a[l][i]*c[e];
    c[e]=-c[e]*a[l][e];
    return re;
}
double simplex() {
    double ans=0;
    while(1){
        int l=0;
        int e=0;
        rep(i,1,cnt)if(c[i]>0) {
            e=i;
            break;
        }
        if(!e)return ans;
        double vg=1e256;
        rep(i,1,m)if(a[i][e]>1e-10){
            if(b[i]/a[i][e]<vg) {
                vg=b[i]/a[i][e];
                l=i;
            }
        }
        ans+=rotate(l,e);
    }
}
double solve() {
    int ans=++cnt;
    rep(i,1,n-1)node[i]=++cnt;
    double ma=0;
    rep(i,1,n)if(val[i]>ma)ma=val[i];
    rep(i,1,n)if(val[i]>ma)ma=val[i];
    
    rep(i,1,n-1){
        ++m;
        a[m][node[i]]=1;
        b[m]=(i*1.)/n;
    }
    rep(i,1,n-1){
        ++m;
        a[m][node[i]]=1;
        if(i==n-1){
            b[m]=1;
            continue;
        }
        a[m][node[i+1]]=-1;
        b[m]=0;
    }
    
    ++m;
    a[m][ans]=1;b[m]=ma;

    rep(i,1,n){
        ++m;
        rep(j,1,i-1)a[m][node[j]]=val[j]-val[j+1];
        a[m][ans]=1;
        b[m]=ma-val[i];
    }
    c[ans]=1;
    return ma-simplex();
}

class TheKFactor {
    public:
    double expectedScore(vector<int> values) {
        n=values.size();
        rep(i,1,n)val[i]=values[i-1];
        return solve();
    }
};

// CUT begin
ifstream data("TheKFactor.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> values, double __expected) {
    time_t startClock = clock();
    TheKFactor *instance = new TheKFactor();
    double __result = instance->expectedScore(values);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> values;
        from_stream(values);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(values, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1471245727;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheKFactor (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
