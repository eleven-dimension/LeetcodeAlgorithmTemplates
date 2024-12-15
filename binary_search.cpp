#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>

// [T, T, T, ..., T, F, F, F, ...]
// find the first position p in [l, r] such that condition(p) is false
#include <optional>
#include <ranges>

enum class BoundType { Lower, Upper };
enum class TargetPosition { First, Last };

std::optional<long long> FindBound(long long l, long long r,
                                   const auto& condition, BoundType bound_type,
                                   TargetPosition target_position) {
  if (r < l) {
    return std::nullopt;
  }
  auto range = std::views::iota(l, r + 1);
  auto iter =
      (target_position == TargetPosition::First ? range.end() : range.begin());
  bool is_upper_bound = (target_position == TargetPosition::Last &&
                         bound_type == BoundType::Lower) ||
                        (target_position == TargetPosition::First &&
                         bound_type == BoundType::Upper);
  auto func = [is_upper_bound](auto&&... args) {
    if (is_upper_bound)
      return std::ranges::upper_bound(std::forward<decltype(args)>(args)...);
    else
      return std::ranges::lower_bound(std::forward<decltype(args)>(args)...);
  };

  auto reversed_condition = [&](long long x) {
    return target_position == TargetPosition::Last ? !condition(x)
                                                   : condition(x);
  };

  auto comparator = [&](auto a, auto b) {
    auto x = is_upper_bound ? b : a;
    return reversed_condition(x);
  };

  iter = func(range, 0, comparator);

  if (target_position == TargetPosition::Last && iter != range.begin()) {
    --iter;
    return *iter;
  }
  if (target_position == TargetPosition::First && iter != range.end()) {
    return *iter;
  }
  return std::nullopt;
}

std::optional<long long> FirstFalse(long long l, long long r,
                                    const auto& condition) {
  return FindBound(l, r, condition, BoundType::Lower, TargetPosition::First);
}

std::optional<long long> FirstTrue(long long l, long long r,
                                   const auto& condition) {
  return FindBound(l, r, condition, BoundType::Upper, TargetPosition::First);
}

std::optional<long long> LastFalse(long long l, long long r,
                                   const auto& condition) {
  return FindBound(l, r, condition, BoundType::Upper, TargetPosition::Last);
}

std::optional<long long> LastTrue(long long l, long long r,
                                  const auto& condition) {
  return FindBound(l, r, condition, BoundType::Lower, TargetPosition::Last);
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