#include <bits/stdc++.h>

struct Range {
    long long l, r;
    mutable long long v;

    Range(long long left, long long right = -1, long long val = 0) : l(left), r(right), v(val) {}

    bool operator < (const Range& ano) const { return l < ano.l; }
};

class ChthollyTree {
public:
    using Iter = std::set<Range>::iterator;

    void Insert(int l, int r, int v) {
        range_set_.emplace(l, r, v);
    }

    // [ , pos - 1]  [pos, ]
    Iter Split(long long pos) {
        Iter iter = range_set_.lower_bound(Range(pos));
        // no need to split
        if (iter != range_set_.end() && iter->l == pos) {
            return iter;
        }
        // split
        iter--;
        auto [left, right, val] = *iter;
        range_set_.erase(iter);
        range_set_.emplace(left, pos - 1, val);
        return range_set_.emplace(pos, right, val).first;
    }

    void Assign(long long l, long long r, long long val) {
        auto iter_r = Split(r + 1);
        auto iter_l = Split(l);
        range_set_.erase(iter_l, iter_r); // [ , )
        range_set_.emplace(l, r, val);
    }

    void Add(long long l, long long r, long long val) {
        auto iter_r = Split(r + 1);
        auto iter_l = Split(l);
        for (; iter_l != iter_r; iter_l++) {
            iter_l->v += val;
        }
    }

    long long Rank(long long l, long long r, long long k) {
        std::vector<std::pair<long long, long long>> pair_vector;
        auto iter_r = Split(r + 1);
        auto iter_l = Split(l);

        for (; iter_l != iter_r; iter_l++) {
            pair_vector.emplace_back(iter_l->v, iter_l->r - iter_l->l + 1);
        }
        std::sort(pair_vector.begin(), pair_vector.end());
        for (auto& p : pair_vector) {
            k -= p.second;
            if (k <= 0) {
                return p.first;
            }
        }
        return -1LL;
    }

    long long Sum(long long l, long long r, long long exp, long long mod) {
        auto pow = [] (long long a, long long b, long long p) {
            long long ans = 1 % p;
            a %= p;
            for (; b; b >>= 1) {
                if (b & 1) {
                    ans = ans * a % p;
                }
                a = a * a % p;
            }
            return ans;
        };
        auto iter_r = Split(r + 1);
        auto iter_l = Split(l);
        long long res = 0;
        for (; iter_l != iter_r; iter_l++) {
            res = (res + (iter_l->r - iter_l->l + 1) * pow(iter_l->v, exp, mod)) % mod;
        }
        return res;
    }

private:
    std::set<Range> range_set_;
};

using ll = long long;
using namespace std;

const ll MOD = 1000000000 + 7;
const ll MaxN = 100000 + 10;

ll n, m;
ll seed, vmax;

ll rd() {
    ll res = seed;
    seed = (seed * 7 + 13) % MOD;
    return res;
}

ll t[MaxN];

int main() {
    ChthollyTree tree;
    cin >> n >> m >> seed >> vmax;

    for (ll i = 1; i <= n; i++) {
        t[i] = (rd() % vmax) + 1;
        tree.Insert(i, i, t[i]);
    }

    tree.Insert(n + 1, n + 1, 0);
    for (ll i = 1; i <= m; ++i) {
        ll op = ll(rd() % 4) + 1;
        ll l = ll(rd() % n) + 1;
        ll r = ll(rd() % n) + 1;

        if (l > r) {
            swap(l, r);
        }

        ll x, y;
        if (op == 3) {
            x = int(rd() % (r - l + 1)) + 1;
        } else {
            x = int(rd() % vmax) + 1;
        }

        if (op == 4) {
            y = int(rd() % vmax) + 1;
        }

        if (op == 1) {
            tree.Add(l, r, x);
        } else if (op == 2) {
            tree.Assign(l, r, x);
        } else if (op == 3) {
            cout << tree.Rank(l, r, x) << endl;
        } else {
            cout << tree.Sum(l, r, x, y) << endl;
        }
    }
}