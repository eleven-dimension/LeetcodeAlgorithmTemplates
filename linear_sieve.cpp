#include <bits/stdc++.h>
using namespace std;

class LinearSieve {
public:
    LinearSieve(size_t n) : is_prime_(n, true) {
        is_prime_[0] = is_prime_[1] = false;
        for (size_t i = 2; i < n; i++) {
            if (is_prime_[i]) {
                primes_.emplace_back(i);
            }
            for (size_t j = 0; j < primes_.size() && i * primes_[j] < n; j++) {
                is_prime_[i * primes_[j]] = false;
                if (i % primes_[j] == 0) {
                    break;
                }
            }
        }
    }

    vector<size_t> GetPrimes() const { return primes_; }

    vector<bool> GetIsPrime() const { return is_prime_; }

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
    auto&& primes = sieve.GetPrimes();
    
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << primes[k - 1] << endl;
    }

    return 0;
}