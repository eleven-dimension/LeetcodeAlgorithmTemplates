#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <iostream>
#include <limits>

template <class T, auto op, auto e>
class SegmentTree {
    static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>, "op must work as T(T, T)");
    static_assert(std::is_convertible_v<decltype(e), std::function<T()>>, "e must work as T()");

public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(size_t n) : SegmentTree(std::vector<T>(n, e())) {}
    SegmentTree(const std::vector<T>& v) : n_(v.size()) {
        data_ = std::vector<T>(n_ * 4 + 0x0430, e());
        Build(1, 0, n_ - 1, v);
    }

    // [l, r)
    T Prod(size_t l, size_t r) {
        assert(0 <= l && l < r && r <= n_);
        return DoProd(1, l, r - 1, 0, n_ - 1);
    }

    void Set(size_t pos, T val) {
        assert(0 <= pos && pos < n_);
        DoSet(1, 0, n_ - 1, pos, val);
    }

private:
    void Build(size_t cur, size_t l, size_t r, const std::vector<T>& v) {
        if (l == r) {
            data_[cur] = v[l];
            return;
        }
        size_t mid = (l + r) / 2;
        Build(cur * 2, l, mid, v);
        Build(cur * 2 + 1, mid + 1, r, v);
        data_[cur] = op(data_[cur * 2], data_[cur * 2 + 1]);
    }

    T DoProd(size_t cur, size_t ql, size_t qr, size_t cur_l, size_t cur_r) {
        if (ql <= cur_l && cur_r <= qr) {
            return data_[cur];
        }
        size_t mid = (cur_l + cur_r) / 2;
        T res = e();
        if (ql <= mid) {
            res = op(res, DoProd(cur * 2, ql, qr, cur_l, mid));
        }
        if (qr > mid) { 
            res = op(res, DoProd(cur * 2 + 1, ql, qr, mid + 1, cur_r));
        }
        return res;
    }

    void DoSet(size_t cur, size_t cur_l, size_t cur_r, size_t pos, T val) {
        if (cur_l == cur_r) {
            data_[cur] = val;
            return;
        }
        size_t mid = (cur_l + cur_r) / 2;
        if (pos <= mid) {
            DoSet(cur * 2, cur_l, mid, pos, val);
        }
        else {
            DoSet(cur * 2 + 1, mid + 1, cur_r, pos, val);
        }
        data_[cur] = op(data_[cur * 2], data_[cur * 2 + 1]);
    }

    std::vector<T> data_;
    size_t n_;
};

using namespace std;

// Luogu P1198 [JSOI2008]
int main() {
    using ll = long long;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, mod;
    cin >> m >> mod;
    
    const int N = 2e5 + 10;
    auto mx = [](ll a, ll b) { return max(a, b); };
    auto e = []() { return -numeric_limits<ll>::max(); };
    vector<ll> v(N, e());
    SegmentTree<ll, mx, e> segment_tree(v);

    int size = 0;
    ll last = 0;
    for (int i = 1; i <= m; i++) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == 'A') {
            ll val = (x + last) % mod;
            segment_tree.Set(size, val);
            size++;
        } else {
            ll res = segment_tree.Prod(size - x, size);
            last = res;
            cout << res << endl;
        }
    }
}