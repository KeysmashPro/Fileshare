#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#pragma GCC optimization("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned long long u64;
typedef signed   long long i64;

// Id & Dist (vertex or edge)
struct idds {
  u64 idx;
  u64 dst;
  bool operator>(const idds& other) const {
    return dst > other.dst;
  }
  bool operator<(const idds& other) const {
    return dst < other.dst;
  }
};

struct bus {
  u64 idx;
  u64 st;
  u64 et;
};

// Better than BFS
i64 dks(vector<vector<bus>>& v, u64 start, u64 end) {
  vector<idds> vrtx(v.size(), {u64(-1), u64(-1)});
  priority_queue<idds, vector<idds>, greater<idds>> pq;
  
  vrtx[start].idx = start;
  vrtx[start].dst = 0;
  pq.push({start, 0});
  
  while (!pq.empty()) {
    u64 c_idx = pq.top().idx;
    u64 c_dst = pq.top().dst;
    pq.pop();

    if (c_dst > vrtx[c_idx].dst) continue;
    if (c_idx == end) { return c_dst; }
    
    for (auto& e : v[c_idx]) {
      u64 new_dst = u64(-1);
      if (c_dst <= e.st)
        new_dst = e.et;
      else
        continue;
      if (new_dst < vrtx[e.idx].dst) {
        vrtx[e.idx].idx = c_idx;
        vrtx[e.idx].dst = new_dst;
        pq.push({e.idx, new_dst});
      }
    }
  }
  return -1;
}

vector<vector<bus>> input(u64 n, u64 m) {
  vector<vector<bus>> adj(n);
  for (u64 i = 0; i < m; ++i) {
    u64 a, at, b, bt;
    cin >> a >> at >> b >> bt;
    a--;
    b--;
    adj[a].push_back({b, at, bt});
  }
  return adj;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  u64  n, m, s, e;
  cin >> n;
  cin >> s >> e;
  s--; e --;
  cin >> m;

  vector<vector<bus>> graph = input(n, m);
  cout << dks(graph, s, e) << endl;
  return 0;
}
