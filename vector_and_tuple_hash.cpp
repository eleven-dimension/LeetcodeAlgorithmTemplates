#include <bits/stdc++.h>

template <class T>
size_t HashCombine(size_t seed, const T& value) {
  return seed ^
         (std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

struct TupleHash {
  size_t operator()(const auto& tuple) const {
    size_t res = 0;
    std::apply(
        [&res](const auto&... args) { ((res = HashCombine(res, args)), ...); },
        tuple);
    return res;
  }
};

template <typename T>
struct is_vector : std::false_type {};

template <typename T, typename Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type {};

struct VectorHash {
  template <typename T>
  size_t operator()(const T& value) const {
    if constexpr (is_vector<T>::value) {
      size_t seed = 0;
      for (const auto& val : value) {
        seed = HashCombine(seed, VectorHash{}(val));
      }
      return seed;
    } else {
      return std::hash<T>{}(value);
    }
  }
};