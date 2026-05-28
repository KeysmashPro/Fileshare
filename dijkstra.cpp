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
  u64 mas;
  bool operator>(const idds& other) const {
    return dst > other.dst;
  }
};

// Better than BFS
u64 dijkstra(vector<vector<idds>>& v, u64 start, u64 end, u64 mas) {
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
    if (c_idx == end) return vrtx[c_idx].dst;
    
    for (auto& e : v[c_idx]) {
      if  (mas > e.mas) continue;
      u64 new_dst = c_dst + e.dst;

      if (new_dst < vrtx[e.idx].dst) {
        vrtx[e.idx].idx = c_idx;
        vrtx[e.idx].dst = new_dst;
        pq.push({e.idx, new_dst});
      }
    }
  }
  return u64(-1);
}

vector<vector<idds>> input(u64 n, u64 m) {
  vector<vector<idds>> res(n);
  for (u64 i = 0; i < m; ++i) {
      u64 a, b, t, w;
      cin >> a >> b >> t >> w;
      --a; --b;
      res[a].push_back({b, t, w});
      res[b].push_back({a, t, w});
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  u64 n, m, start, end; cin >> n >> m;
  // max time = 1440
  if (m == 0) {
    if (n == 1) cout << 10000000 << endl;
    else cout << 0 << endl;
    return 0;
  }

  vector<vector<idds>> graph = input(n, m);
  vector<u64> mases;
  mases.reserve(2*m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      mases.push_back(graph[i][j].mas);
    }
  }
  sort(mases.begin(), mases.end());
  auto last = unique(mases.begin(), mases.end());
  mases.erase(last, mases.end());
  
  //bin-search
  u64 res = 0;
  i64 left = 0;
  i64 right = mases.size() - 1;
  while(left <=  right) {
    i64 mid = left + (right - left) / 2;
    u64 ct = dijkstra(graph, 0, n-1, mases[mid]);
    if (ct <= 1440) {
      res = mases[mid];
      left = mid+1;
    } else {
      right = mid-1;
    }
  }

  cout << (res <= 3000000 ? 0 : (res - 3000000) / 100) << endl; 
  return 0;
}
