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
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
 
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
 
using namespace std;
  typedef vector<pair<int, int> > vpii; 
 
static int bsf(uint64_t x) {
#if defined(__GNUC__)
  return __builtin_ctzll(x);
#else
  unsigned long res;
  _BitScanForward64(&res, x);
  return res;
#endif
}
 
static int popcount(uint64_t x) {
#if defined(__GNUC__)
  return __builtin_popcountll(x);
#else
  return (int)__popcnt64(x);
#endif
}
 
struct BitSet {
  uint64_t data;
  BitSet() : data(0) {}
 
  explicit operator bool() const {
    return data != 0;
  }
 
  bool get(unsigned pos) const {
    return data >> pos & 1;
  }
 
  void set(unsigned pos) {
    data |= uint64_t(1) << pos;
  }
 
  void unset(unsigned pos) {
    data &= ~(uint64_t(1) << pos);
  }
 
  int count() const {
    return popcount(data);
  }
 
  BitSet operator&(BitSet that) const {
    BitSet res;
    res.data = data & that.data;
    return res;
  }
 
  bool isIntersectTo(const BitSet &that) const {
    return bool(*this & that);
  }
 
  int getSingleton() const {
    if(data == 0 || (data & (data - 1)) != 0)
      return -1;
    else
      return bsf(data);
  }
};
 
class MaximumCliqueBranchAndBound {
public:
  typedef uint8_t Vertex;
 
  BitSet maximumClique(const vector<BitSet> &originalGraph) {
    graph = originalGraph;
    int N = (int)graph.size();
    levels.assign(N, BitSet());
    vertexLevel.assign(N, -1);
    vertexDegree.assign(N, -1);
    BitSet initSet;
    for(int i = 0; i < N; ++ i)
      initSet.set(i);
    globalBuffer.resize(N * N * 2 + N + N * 3 * N);
    levelVertices.resize(N);
    rep(i, N)
      levelVertices[i].first = globalBuffer.data() + i * N;
    degreeVertices.resize(N);
    rep(i, N)
      degreeVertices[i].first = globalBuffer.data() + (N + i) * N;
    Vertex *initOrder = globalBuffer.data() + N * N * 2,
      *nextBuffer = initOrder + N;
    rep(i, N)
      initOrder[i] = i;
 
    curClique = maxClique = BitSet();
    curSize = maxSize = 0;
    numRecs = 0;
 
    rec(initSet, initOrder, N, nextBuffer);
 
    //cerr << "numRecs = " << numRecs << endl;
    return maxClique;
  }
 
private:
 
  void rec(BitSet remSet, const Vertex *originalOrder, int originalOrderSize, Vertex *buffer) {
    ++ numRecs;
 
    int numLevels = 0, numVertices = 0;
    for(int ix = 0; ix < originalOrderSize; ++ ix) {
      int p = originalOrder[ix];
      if(!remSet.get(p)) continue;
      ++ numVertices;
      int k = 0;
      while(k < numLevels && levels[k].isIntersectTo(graph[p]))
        ++ k;
      if(k == numLevels) {
        levels[k] = BitSet();
        ++ numLevels;
      }
      levels[k].set(p);
      vertexLevel[p] = k;
      vertexDegree[p] = (remSet & graph[p]).count();
 
      int threshold = maxSize - curSize;
      if(k > threshold && k == numLevels - 1) {
        reNumber(p, k, threshold);
        if(!levels[k])
          -- numLevels;
      }
    }
 
    Vertex *levelOrder = buffer,
      *levelOffsets = levelOrder + numVertices,
      *degreeOrder = levelOffsets + numLevels,
      *nextBuffer = degreeOrder + numVertices;
    for(int k = 0; k < numLevels; ++ k)
      levelVertices[k].second = 0;
    for(int d = 0; d < numVertices; ++ d)
      degreeVertices[d].second = 0;
 
    for(int ix = 0; ix < originalOrderSize; ++ ix) {
      int v = originalOrder[ix];
      if(remSet.get(v)) {
        {
          auto &p = levelVertices[vertexLevel[v]];
          p.first[p.second ++] = v;
        }
        {
          auto &p = degreeVertices[vertexDegree[v]];
          p.first[p.second ++] = v;
        }
      }
    }
    for(int k = 0, num = 0; k < numLevels; ++ k) {
      levelOffsets[k] = num;
      auto p = levelVertices[k];
      for(int i = 0; i < p.second; ++ i)
        levelOrder[num ++] = p.first[i];
    }
    for(int d = numVertices - 1, num = 0; d >= 0; -- d) {
      auto p = degreeVertices[d];
      for(int i = 0; i < p.second; ++ i)
        degreeOrder[num ++] = p.first[i];
    }
 
    for(int i = numVertices; ; -- i) {
      int threshold = max(maxSize - curSize, 0);
      if(threshold >= numLevels || i <= levelOffsets[threshold])
        break;
 
      int u = levelOrder[i - 1];
 
      curClique.set(u), ++ curSize;
 
      BitSet newSet = remSet & graph[u];
      if(newSet) {
        rec(newSet, degreeOrder, numVertices, nextBuffer);
      } else if(curSize > maxSize) {
        maxClique = curClique, maxSize = curSize;
      }
      curClique.unset(u), -- curSize;
      remSet.unset(u);
    }
  }
 
  void reNumber(int p, int k, int threshold) {
    for(int i = 0; i < threshold; ++ i) {
      BitSet S = graph[p] & levels[i];
      int q = S.getSingleton();
      if(q == -1) continue;
      for(int j = i + 1; j <= threshold; ++ j) {
        if(graph[q] & levels[j]) continue;
        levels[k].unset(p);
        levels[i].unset(q);
        levels[i].set(p);
        levels[j].set(q);
        vertexLevel[p] = i;
        vertexLevel[q] = j;
        return;
      }
    }
  }
 
  vector<BitSet> graph;
  BitSet curClique, maxClique;
  int curSize, maxSize;
 
  vector<BitSet> levels;
  vector<int> vertexLevel, vertexDegree;
  vector<pair<Vertex*, int> > levelVertices;
  vector<pair<Vertex*, int> > degreeVertices;
  vector<Vertex> globalBuffer;
  long long numRecs;
};
 
struct Clicounting {
  int count(vector <string> g) {
    int n = (int)g.size();
    vpii qs;
    rep(i, n) reu(j, i + 1, n) {
      if(g[i][j] == '?')
        qs.push_back(make_pair(i, j));
    }
    int ans = 0;
    MaximumCliqueBranchAndBound mc;
    rep(s, 1 << (int)qs.size()) {
      vector<BitSet> gg(n);
      rep(i, n) rep(j, n) if(g[i][j] == '1')
        gg[i].set(j);
      rep(i, qs.size()) if(s >> i & 1) {
        int a, b; a = qs[i].first; b = qs[i].second;
        gg[a].set(b);
        gg[b].set(a);
      }
      ans += (int)mc.maximumClique(gg).count();
    }
    return ans;
  }
};

// CUT begin
ifstream data("Clicounting.sample");

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

bool do_test(vector<string> g, int __expected) {
    time_t startClock = clock();
    Clicounting *instance = new Clicounting();
    int __result = instance->count(g);
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
        vector<string> g;
        from_stream(g);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(g, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1472823756;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Clicounting (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
