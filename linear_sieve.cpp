#include <bits/stdc++.h>
using namespace std;

class LinearSieve {
public:
    LinearSieve(size_t n) : is_prime_(n + 1, true) {
        primes_.reserve(n / std::log(n));
        is_prime_[0] = is_prime_[1] = false;
        for (size_t i = 2; i <= n; i++) {
            if (is_prime_[i]) {
                primes_.emplace_back(i);
            }
            for (size_t j : primes_) {
                if (i * j > n) {
                    break;
                }
                is_prime_[i * j] = false;
                if (i % j == 0) {
                    break;
                }
            }
        }
    }

    const vector<size_t>& GetPrimes() const {
        return primes_;
    }

    const vector<bool>& GetIsPrime() const {
        return is_prime_;
    }

private:
    vector<bool> is_prime_;
    vector<size_t> primes_;
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    LinearSieve sieve(n);
    const auto& primes = sieve.GetPrimes();

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << primes[k - 1] << endl;
    }

    return 0;
}
