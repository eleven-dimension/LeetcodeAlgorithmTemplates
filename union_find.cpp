#include <bits/stdc++.h>

template <std::integral T>
class UnionFind {
public:
    UnionFind(T size) {
        parent.resize(size);
        rank.resize(size, 0);
        std::iota(parent.begin(), parent.end(), 0);
    }

    T find(T x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(T x, T y) {
        T rootX = find(x);
        T rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(T x, T y) {
        return find(x) == find(y);
    }

private:
    std::vector<T> parent;
    std::vector<T> rank;
};

int main() {
    UnionFind<int> uf(10);

    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(4, 5);

    std::cout << std::boolalpha;
    std::cout << "1 and 3 connected: " << uf.connected(1, 3) << std::endl;
    std::cout << "1 and 4 connected: " << uf.connected(1, 4) << std::endl;

    uf.unite(3, 4);

    std::cout << "1 and 5 connected: " << uf.connected(1, 5) << std::endl;
}