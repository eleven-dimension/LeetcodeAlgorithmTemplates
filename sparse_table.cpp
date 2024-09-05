#include <bits/stdc++.h>

namespace fast_io {
    template<typename T>
    inline void read(T& t) {
        T x = 0, f = 1;
        char c = getchar();
        for (; !isdigit(c); c = getchar()) {
            if (c == '-') {
                f = -1;
            }
        }
        for (; isdigit(c); c = getchar()) {
            x = (x << 3) + (x << 1) + (c ^ '0');
        }
        t = x * f;
    }

    template<typename T>
    inline void write(T x) {
        char f[200];
        if (x == 0) {
            putchar('0');
            return;
        }
        T tmp = x > 0 ? x : -x;
        if (x < 0) {
            putchar('-');
        }
        int cnt = 0;
        while (tmp > 0) {
            f[cnt++] = tmp % 10 + '0';
            tmp /= 10;
        }
        while (cnt > 0) {
            putchar(f[--cnt]);
        }
    }

    template<typename T>
    inline void writes(T x) {
        write(x);
        putchar(' ');
    }

    template<typename T>
    inline void writee(T x) {
        write(x);
        puts("");
    }
}

template <class T, auto op, auto e>
class SparseTable {
    static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>, "op must work as T(T, T)");
    static_assert(std::is_convertible_v<decltype(e), std::function<T()>>, "e must work as T()");

public:
    SparseTable() : SparseTable(0) {}
    SparseTable(size_t n) : SparseTable(std::vector<T>(n, e())) {}
    SparseTable(const std::vector<T>& v) : n_(v.size()), m_(log2(v.size())) {
        table_ = std::vector<std::vector<T>>(n_, std::vector<T>(m_, e()));
        for (size_t i = 0; i < n_; i++) {
            table_[i][0] = v[i];
        }
        for (size_t j = 1; j <= m_; j++) {
            for (size_t i = 0; i <= n_ - (1 << j); i++) {
                table_[i][j] = op(table_[i][j - 1], table_[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T Query(size_t l, size_t r) {
        assert(0 <= l && l < r && r <= n_);
        size_t len = log2(r - l);
        return op(table_[l][len], table_[r - (1 << len)][len]);
    }

private:
    std::vector<std::vector<T>> table_;
    size_t n_;
    size_t m_;
};

using namespace std;
using namespace fast_io;

// Luogu P3865
int main() {
    int n, m;
    read(n); read(m);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }
    auto mx = [](int a, int b) { return max(a, b); };
    auto e = []() { return -numeric_limits<int>::max(); };
    SparseTable<int, mx, e> st(a);
    
    for (int i = 1; i <= m; i++) {
        int l, r;
        read(l), read(r);

        int res = st.Query(l - 1, r);
        writee(res);
    }
}