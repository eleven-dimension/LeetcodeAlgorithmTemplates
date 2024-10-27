#include <bits/stdc++.h>

template <std::integral T>
class UnionFind {
 public:
  UnionFind(T size) {
    parent_.resize(size);
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  T Find(T x) {
    if (parent_[x] != x) {
      parent_[x] = Find(parent_[x]);
    }
    return parent_[x];
  }

  void Unite(T x, T y) {
    T root_x = Find(x);
    T root_y = Find(y);
    parent_[root_x] = root_y;
  }

  bool Connected(T x, T y) { return Find(x) == Find(y); }

 private:
  std::vector<T> parent_;
};

int main() {
  UnionFind uf(10);

  uf.Unite(1, 2);
  uf.Unite(2, 3);
  uf.Unite(4, 5);

  std::cout << std::boolalpha;
  std::cout << "1 and 3 connected: " << uf.Connected(1, 3) << std::endl;
  std::cout << "1 and 4 connected: " << uf.Connected(1, 4) << std::endl;

  std::cout << "1 and 5 connected: " << uf.Connected(1, 5) << std::endl;

  uf.Unite(3, 4);

  std::cout << "1 and 5 connected: " << uf.Connected(1, 5) << std::endl;
}