#include <iostream>
#include <vector>

int matrix_to_list(vector<bool>, uint32_t size) {
  for (int i = 0; i < sieze; ++i) {
    for
}

void bfs_on_list(const vector<vector<uint32_t>>& vertex, uint32_t start)
{
  vector<uint32_t> shortcut(vertex.size(), 0);
  vector<uint32_t> distance(vertex.size(), 0);
  queue<uint32_t> queue;

  shortcut[start] = start;
  distance[start] = 1;
  queue.push(start);

  while (!queue.empty()) {
    uint32_t v = queue.front();
    queue.pop(); // remove v
    for ( const auto &i : vertex[v]) {
      if (distance[i] == 0) {
        distance[i] = distance[v] + 1;
        shortcut[i] = v;
        queue.push(i);
      } else { continue; }
    }
  }
}

int main() {
  // graph init
  int n_size = 10;
  vector<vector<int>> vertex(n);
  return 0;
}
