#include <bits/stdc++.h>

template<std::integral IndexType, typename ValueType>
class FenwickTree {
public:
    FenwickTree(IndexType size) : size_(size), tree_(size + 1, 0) {}

    void add(IndexType index, ValueType value) {
        for (; index <= size_; index += lowbit(index)) {
            tree_[index] += value;
        }
    }

    ValueType sum(IndexType index) const {
        ValueType result = 0;
        for (; index > 0; index -= lowbit(index)) {
            result += tree_[index];
        }
        return result;
    }

    ValueType rangeSum(IndexType left, IndexType right) const {
        return sum(right) - sum(left - 1);
    }

private:
    IndexType lowbit(IndexType x) const {
        return x & -x;
    }

    IndexType size_;
    std::vector<ValueType> tree_;
};

int main() {
    size_t n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 1);
    FenwickTree<size_t, int> fenwickTree(n);

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