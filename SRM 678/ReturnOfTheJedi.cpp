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

class ReturnOfTheJedi {
    public:
    struct frac {
      int64_t top;
      int64_t bot;
      
      bool operator<(const frac& that) const {
        return top * that.bot < bot * that.top;
      }
      
      bool operator==(const frac& that) const {
        return top * that.bot == bot * that.top;
      }
    }; 
    struct event {
      int x, y;
      frac when;
      bool operator<(const event& that) const {
        if (when == that.when) {
          if (y != that.y)
            return y > that.y;
          return x > that.x;
        }
        return when < that.when;
      }
    };
 
    vector<double> minimalExpectation(vector<int> x, vector<int> p) {
      int N = x.size();
      vector< pair<int, int> > A(N);
      for (int i = 0; i < N; ++i)
        A[i] = make_pair(x[i], p[i]);
      sort(A.begin(), A.end(), [&](pair<int, int> x, pair<int, int> y) {
        if (x.second != y.second)
          return x.second > y.second;
        return x.first < y.first;
      });
      
      vector<event> E;
      E.reserve(N * N);
      for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
          if (A[i].second != A[j].second)
            E.emplace_back(event{i, j, frac{1LL * A[j].first * A[j].second - 1LL * A[i].first * A[i].second, A[i].second - A[j].second}});
      
      sort(E.begin(), E.end());
      
      vector<int> position(N);
      for (int i = 0; i < N; ++i)
        position[i] = i;
      vector<int> array(N);
      for (int i = 0; i < N; ++i)
        array[i] = i;
      vector<double> answer(N, 1e50);
      for (auto &e: E) {
        int64_t sum = 0;
        long double prob = 1.0;
        for (int i = 0; i < N; ++i) {
          sum += A[array[i]].first;
          prob *= A[array[i]].second / double(100000);
          answer[i] = min(answer[i], double(sum * prob));
        }
        
        int whereX = position[e.x];
        int whereY = position[e.y];
        swap(array[whereX], array[whereY]);
        position[array[whereX]] = whereX;
        position[array[whereY]] = whereY;
      }
      
      int64_t sum = 0;
      long double prob = 1.0;
      for (int i = 0; i < N; ++i) {
        sum += A[array[i]].first;
        prob *= A[array[i]].second / double(100000);
        answer[i] = min(answer[i], double(sum * prob));
      }
      
      return answer;
    }
};

// CUT begin
ifstream data("ReturnOfTheJedi.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool double_vector_equal (const vector<double> &expected, const vector<double> &received) {
    if (expected.size() != received.size()) return false;
    int n = expected.size();
    for (int i = 0; i < n; ++i)
        if (!double_equal(expected[i], received[i])) return false;
    return true;
}

bool do_test(vector<int> x, vector<int> p, vector<double> __expected) {
    time_t startClock = clock();
    ReturnOfTheJedi *instance = new ReturnOfTheJedi();
    vector<double> __result = instance->minimalExpectation(x, p);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_vector_equal(__expected, __result)) {
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
        vector<int> x;
        from_stream(x);
        vector<int> p;
        from_stream(p);
        next_line();
        vector<double> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, p, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1474037586;
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
        cout << "ReturnOfTheJedi (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
