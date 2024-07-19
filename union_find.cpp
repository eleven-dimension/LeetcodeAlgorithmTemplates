#include <bits/stdc++.h>

template <std::integral T>
class UnionFind {
public:
    UnionFind(T size) {
        parent_.resize(size);
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    T find(T x) {
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    void unite(T x, T y) {
        T root_x = find(x);
        T root_y = find(y);
        parent_[root_x] = root_y;
    }

    bool connected(T x, T y) {
        return find(x) == find(y);
    }

private:
    std::vector<T> parent_;
};

int main() {
    UnionFind uf(10);

    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(4, 5);

    std::cout << std::boolalpha;
    std::cout << "1 and 3 connected: " << uf.connected(1, 3) << std::endl;
    std::cout << "1 and 4 connected: " << uf.connected(1, 4) << std::endl;

    std::cout << "1 and 5 connected: " << uf.connected(1, 5) << std::endl;

    uf.unite(3, 4);

    std::cout << "1 and 5 connected: " << uf.connected(1, 5) << std::endl;
}