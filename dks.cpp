#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef unsigned long long u32;

// Id & Dist (vertex or edge)
struct idds {
  u32 idx;
  u32 dst;
  u32 mas;
  bool operator>(const idds& other) const {
    return dst > other.dst;
  }
};

vector<vector<idds>> edg_to_adj(vector<u32> v, u32 n, u32 k) {
  vector<vector<idds>> res(n);
  for (int i = 0; i < k; ++i)
    cin >> v[4*i+0] >> v[4*i+1] >> v[4*i+2] >> v[4*i+3];

  for (u32 i = 0; i < v.size()/4; ++i) {
    u32 a = v[4*i+0];
    u32 b = v[4*i+1];
    u32 d = v[4*i+2];
    u32 m = v[4*i+3];
    res[a].push_back({b, d, m});
    res[b].push_back({a, d, m});
  }
  return res;
}

vector<vector<idds>> matrix_to_adj(u32 n) {
  vector<vector<idds>> res(n);
  int d;
  for (u32 i = 0; i < n; ++i) {
    for (u32 j = 0; j < n; ++j) {
      cin >> d;
      if (d >= 0)
        res[i].push_back({j, (u32)d});
    }
  }
  return res;
}

// Better than BFS
int dijkstra(vector<vector<idds>>& v, u32 start, u32 end) {
  vector<idds> vrtx(v.size(), {u32(-1), u32(-1)});
  priority_queue<idds, vector<idds>, greater<idds>> pq;
  
  vrtx[start].idx = start;
  vrtx[start].dst = 0;
  pq.push({start, 0});
  
  while (!pq.empty()) {
    u32 c_idx = pq.top().idx;
    u32 c_dst = pq.top().dst;
    pq.pop();

    if (c_dst > vrtx[c_idx].dst) continue;
    if (c_idx == end) return vrtx[c_idx].dst;
    
    for (u32 i = 0; i < v[c_idx].size(); ++i) {
      u32 neighbor = v[c_idx][i].idx;
      u32 e_weight = v[c_idx][i].dst;
      u32 new_dst = c_dst + e_weight;

      if (new_dst < vrtx[neighbor].dst) {
        vrtx[neighbor].idx = c_idx;
        vrtx[neighbor].dst = new_dst;
        pq.push({neighbor, new_dst});
      }
    }
  }
  return -1;
}

int main() {
  u32 n, m, start, end;
  cin >> n >> m;

  vector<u32> v(m*4);
  vector<vector<idds>> graph = edg_to_adj(v, n, m);
  vector<u32> mas(m);
  for (int i = 0; i < m; ++i) {
    mas.push_back(graph[i*4+3]);
  }

  cout << dijkstra(graph, 0, n-1) << endl;
  return 0;
}
