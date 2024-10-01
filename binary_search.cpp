#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>

// [T, T, T, ..., T, F, F, F, ...]
// find the first position p in [l, r] such that condition(p) is false
#include <optional>
#include <ranges>

enum class BoundType { Lower, Upper };

std::optional<long long> FindFirst(long long l, long long r, auto condition,
                                   BoundType bound_type) {
  if (r < l) {
    return std::nullopt;
  }
  auto range = std::views::iota(l, r + 1);
  auto iter = range.end();

  if (bound_type == BoundType::Lower) {
    iter = std::ranges::lower_bound(
        range, 0, [&](long long x, auto) { return condition(x); });
  } else {
    iter = std::ranges::upper_bound(
        range, 0, [&](auto, long long x) { return condition(x); });
  }

  if (iter != range.end()) {
    return *iter;
  }
  return std::nullopt;
}

std::optional<long long> FirstFalse(long long l, long long r, auto condition) {
  return FindFirst(l, r, condition, BoundType::Lower);
}

std::optional<long long> FirstTrue(long long l, long long r, auto condition) {
  return FindFirst(l, r, condition, BoundType::Upper);
}

using namespace std;

int main() {
  vector<int> f = {1, 2, 3, 4, 6};

  {
    auto result = FirstTrue(0, 4, [&](int pos) { return f[pos] > 3; });
    if (result) {
      cout << *result << endl;
    } else {
      cout << -1 << endl;
    }
  }

  {
    auto result = FirstTrue(0, 4, [&](int pos) { return f[pos] > 10; });
    if (result) {
      cout << *result << endl;
    } else {
      cout << -1 << endl;
    }
  }

  {
    auto result = FirstFalse(0, 4, [&](int pos) { return f[pos] <= 1; });
    if (result) {
      cout << *result << endl;
    } else {
      cout << -1 << endl;
    }
  }

  {
    auto result = FirstFalse(0, 4, [&](int pos) { return f[pos] > 0; });
    if (result) {
      cout << *result << endl;
    } else {
      cout << -1 << endl;
    }
  }
}