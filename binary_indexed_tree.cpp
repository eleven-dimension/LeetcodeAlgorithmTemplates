#include <bits/stdc++.h>

// NOTE: index starts from 1.
template <typename ValueType = int>
class FenwickTree {
 public:
  FenwickTree(size_t size) : tree_(size + 1) {}

  void add(size_t index, ValueType value) {
    for (size_t tree_size = size(); index <= tree_size;
         index += lowbit(index)) {
      tree_[index] += value;
    }
  }

  ValueType rangeSum(size_t left, size_t right) const {
    return sum(right) - sum(left - 1);
  }

 private:
  ValueType sum(size_t index) const {
    ValueType result = 0;
    for (; index > 0; index -= lowbit(index)) {
      result += tree_[index];
    }
    return result;
  }

  size_t lowbit(size_t x) const { return x & -x; }

  size_t size() const { return tree_.size() - 1; }

  std::vector<ValueType> tree_;
};

int main() {
  size_t n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1);
  FenwickTree fenwickTree(n);

  for (size_t i = 1; i <= n; i++) {
    std::cin >> a[i];
    fenwickTree.add(i, a[i]);
  }

  for (size_t i = 0; i < m; i++) {
    size_t type, b, c;
    std::cin >> type >> b >> c;

    if (type == 1) {
      fenwickTree.add(b, c);
    } else {
      std::cout << fenwickTree.rangeSum(b, c) << std::endl;
    }
  }

  return 0;
}