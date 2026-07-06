#include <iostream>
#include <vector>

typedef unsigned long long u64;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(NULL);
  std::cin.tie(NULL);

  std::vector<u64> n(1000000, 0);
  for (u64 i = 0; i < n.size(); ++i) { n[i] = i + 2; }

  for (const auto& x : n) {
    for (u64 i = x * x - 2; i < n.size(); i += x) {
      n[i] = 0;
    }
  }

  for (const auto& x : n) {
    if (x) std::cout << x << '\n';
  }
  return 0;
}

