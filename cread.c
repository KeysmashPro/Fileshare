#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long u64;
int main(void) {
  u64 s = 1000000;
   u64 *n = malloc(s * sizeof(u64));
  for (u64 i = 0; i < s; ++i) n[i] = i + 2;

  for (u64 idx = 0; idx < s; ++idx) {
    u64 x = n[idx];
    for (u64 i = x * x - 2; i < s; i += x)
      n[i] = 0;
  }
  
  u64 t;
  for (u64 i = 0; i < s - 8; ++i) {
    if (n[i] && n[i + 6] && n[i + 12]) {
      t = n[i];
      printf("%llu %llu %llu\n", t, t + 6, t + 12);
    }
  }

  free(n);
  return 0;
}
