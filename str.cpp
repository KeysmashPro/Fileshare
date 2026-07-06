#include <iostream>
#include <vector>
#include <string>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")

typedef unsigned long long u64;
typedef signed   long long i64;

using namespace std;

int main(void) {
  string s = "0123456789abcdef";
  cout << s.length() << '\n';
  int a;
  cin >> a;
  cin >> a;
  return 0;
}
