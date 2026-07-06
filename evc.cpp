#include <iostream>
#include <vector>

typedef unsigned long long u64;
typedef signed   long long i64;
typedef double f64;

int main() {
  std::ios::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  i64 n, m, s;
  std::cin >> n >> m;
  
  s = n;
  while (m) {
    i64 t = m;
    m = n % m;
    n = t;
  }

  std::cout << n << "\n\n" ;

  std::vector<u64> v(s);
  for (u64 i = 0; i < v.size(); ++i) { v[i] = i; }
  
  for (u64 i = 2; i * i < v.size(); ++i) {
    if (!v[i]) continue;
    for (u64 j = i * i; j < v.size(); j += i) {
      v[j] = 0;
    }
  }
  

  for (u64 j = 2; j < v.size(); ++j) {
    if (v[j]) std::cout << j << " ";
  }

  return 0;
}

