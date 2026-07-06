#include <bits/stdc++.h>

typedef unsigned long long u64;
typedef signed   long long i64;
typedef double f64;

using namespace std;


// big prime number
#define BPN 1000000007

/*---/
1 2 3
4 5 6
7 8 9
- 0 -
/---*/

int main() {
  std::ios::sync_with_stdio(false);
  cout.tie(NULL);
  cin.tie(NULL);
  
  std::vector<vector<u64>> board = {
    {4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9},
    {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}
  };

  std::vector<u64> curr(board.size(), 1);
  std::vector<u64> prev(board.size(), 1);
  u64 length =  12;

  for (int d = 1; d < length; ++d) {
    swap(prev, curr);
    for (int i = 0; i < board.size(); ++i) {
      curr[i] = 0;
      for(int j = 0; j < board[i].size(); ++j)
        curr[i] += (prev[ board[i][j] ] % BPN);
    }
  }
  
  u64 res = 0;
  for (auto& x : curr)
    res += x % BPN;
  std::cout << res % BPN << endl;
  return 0;
}

