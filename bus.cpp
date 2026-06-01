#include <iostream>
#include <vector>
#include <queue>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")

typedef unsigned long long u64;
typedef signed   long long i64;

using namespace std;

struct idds {
  u64 idx;
  u64 dst;
  bool operator>(const idds& other) const { return dst > other.dst; }
  bool operator<(const idds& other) const { return dst < other.dst; }
};

struct bus {
  u64 destanation;
  u64 interval;
  u64 duration;
};

i64 dks(vector<vector<bus>>& v, u64 start, u64 end, u64 t) {
  vector<idds> vrtx(v.size(), {u64(-1), u64(-1)});
  priority_queue<idds, vector<idds>, greater<idds>> pq;
  u64 new_t;
  
  vrtx[start] = {start, t};
  pq.push({start, t});

  while (!pq.empty()) {
    u64 c_idx = pq.top().idx; // curent index
    u64 c_t = pq.top().dst;   // current sum of times
    pq.pop();

    if (c_t > vrtx[c_idx].dst) continue;
    if (c_idx == end) return c_t;

    for (const auto& e : v[c_idx]) {
      if (c_t % e.interval == 0) { new_t = c_t + e.duration; }
      else { new_t = c_t - (c_t % e.interval) + e.interval + e.duration; }
      if (new_t < vrtx[e.destanation].dst) {
        vrtx[e.destanation] = {c_idx, new_t};
        pq.push({e.destanation, new_t});
      }
    }
  }
  cout << -1 << '\n';
  exit(EXIT_SUCCESS);
}

vector<vector<bus>> input(u64 n, u64 m) {
  vector<vector<bus>> res(n);
  for (u64 i = 0; i < m; ++i) {
    u64 a, b, c, d;
    cin >> a >> b >> c >> d;
    a--; b--;
    res[a].push_back({b, c, d});
  }
  return res;
}

int main() {
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  u64 n, m, cp;
  cin >> n >> m;
  auto v = input(n, m);

  cin >> cp;
  vector<u64> p;
  p.resize(cp);
  for (u64 i = 0; i < cp; ++i) {
    u64 t;
    cin >> t;
    p[i] = t - 1;
  }
  
  i64 t = 0;
  for (int i = 0; i < (cp-1); ++i) {
    t = dks(v, p[i], p[i+1], t);
  }

  cout << t << "\n";
  return 0;
}
