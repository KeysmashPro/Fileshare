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

// Better than BFS
void dks(vector<vector<idds>>& v, vector<u64> g, u64 start) {
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
    
    for (auto& e : v[c_idx]) {
      u64 new_dst = c_dst + e.dst;
      if (new_dst < vrtx[e.idx].dst) {
        vrtx[e.idx].idx = c_idx;
        vrtx[e.idx].dst = new_dst;
        pq.push({e.idx, new_dst});
      }
    }
  }
  vector<idds> res;
  for (auto& i : g) {
    res.push_back({i, vrtx[i].dst});
  }

  sort(res.begin(), res.end());
  for (auto& i : res) {
    cout << i.idx + 1 << " " << i.dst << endl;
  }
}

vector<vector<idds>> input(u64 n, u64 m) {
  vector<vector<idds>> adj(n);
  for (u64 i = 0; i < m; ++i) {
    u64 a, b, d;
    cin >> a >> b >> d;
    a--; b--;
    adj[a].push_back({b, d});
    adj[b].push_back({a, d});
  }
  return adj;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  u64  n, m, k, c;
  cin >> n >> m >> k >> c;
  c--;

  vector<u64> g(k);
  for (int i = 0; i < k; ++i) {
    cin >> g[i];
    g[i]--;
  }

  vector<vector<idds>> graph = input(n, m);

  dks(graph, g, c);
  return 0;
}
