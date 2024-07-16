#include <bits/stdc++.h>

template <std::integral T>
class PrefixSum {
public:
    PrefixSum(const std::vector<T>& data) {
        prefix_sums_.resize(data.size() + 1, 0);
        std::partial_sum(data.begin(), data.end(), prefix_sums_.begin() + 1);
    }

    T sum(size_t left, size_t right) const {
        if (left > right || right >= prefix_sums_.size() - 1) {
            throw std::out_of_range("Invalid range");
        }
        return prefix_sums_[right + 1] - prefix_sums_[left];
    }

private:
    std::vector<T> prefix_sums_;
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    PrefixSum<int> ps(data);

    int result = ps.sum(1, 3);
    std::cout << "Sum from index 1 to 3: " << result << std::endl;

    return 0;
}