#include <bits/stdc++.h>

template <class T>
class PrefixSum {
public:
    PrefixSum(const std::vector<T>& data) {
        prefix_sums_.resize(data.size());
        std::partial_sum(data.begin(), data.end(), prefix_sums_.begin());
    }

    T sum(size_t left, size_t right) const {
        if (left > right || right >= prefix_sums_.size()) {
            throw std::out_of_range("Invalid range");
        }
        return prefix_sums_[right] - (left == 0 ? 0 : prefix_sums_[left - 1]);
    }

private:
    std::vector<T> prefix_sums_;
};

int main() {
    {
        std::vector<int> data = {1, 2, 3, 4, 5};
        PrefixSum ps(data);

        int result = ps.sum(1, 3);
        std::cout << "Sum from index 1 to 3: " << result << std::endl;
    }

    {
        std::vector data = {1.0, 2.0};
        PrefixSum ps(data);

        double result = ps.sum(0, 1);
        std::cout << "Sum from index 0 to 1: " << result << std::endl;
    }

    return 0;
}
