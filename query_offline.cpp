#include <bits/stdc++.h>

#include <ranges>

std::vector<int> OfflineQueries(
    const std::vector<std::vector<int>>& queries,
    const std::function<bool(const std::vector<int>&, const std::vector<int>&)>&
        cmp) {
  std::vector<int> indices(queries.size());
  for (int i = 0; i < queries.size(); ++i) {
    indices[i] = i;
  }
  std::ranges::sort(indices,
                    [&](int a, int b) { return cmp(queries[a], queries[b]); });
  return indices;
}

int main() {}
