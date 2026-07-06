#include <iostream>
#include <vector>
#include <tuple>

typedef unsigned long long u64;
typedef signed   long long i64;
typedef double f64;

using namespace std;
const i64 INF = 1e18;

void bfa(i64 n, i64 m, i64 s, f64 c) {
  vector<tuple<i64, i64, f64, f64, f64, f64>> v(m);
  vector<f64> bt(n, 0);
  //queue<i64> q;
  // not done yet spfa
  //q.push(s);
  bt[s] = c;

  i64 a, b;
  f64 rab, cab, rba, cba;
  for (i64 i = 0; i < m; ++i) {
    cin >> a >> b >> rab >> cab >> rba >> cba;
    a--; b--;
    v[i] = {a, b, rab, cab, rba, cba};
  }

  // While improve
  for (i64 i = 0; i < 100 * n; ++i){
    for (i64 j = 0; j < m; ++j) {
      tie(a, b, rab, cab, rba, cba) = v[j];
      if (bt[a] > cab) {
        f64 new_bc = (bt[a] - cab) * rab;
        if (bt[b] < new_bc) bt[b] = new_bc;
      } 
      if (bt[b] > cba) {
        f64 new_bc = (bt[b] - cba) * rba;
        if (bt[a] < new_bc) bt[a] = new_bc;
      }
    }
    if (bt[s] > c) { cout << "YES\n"; return; }
  }
  cout << "NO\n";
  return;
}

int main(void) {
  ios::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  i64 n, m, s;
  f64 c;
  cin >> n >> m >> s >> c;
  s--;
  
  bfa(n, m, s, c);
  return(0);
}

