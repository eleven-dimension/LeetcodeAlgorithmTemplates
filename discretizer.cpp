#include <bits/stdc++.h>

template<typename T>
class Discretizer {
public:
    Discretizer(const std::vector<T>& input) {
        sorted_ = input;
        std::ranges::sort(sorted_);

        auto it = std::unique(sorted_.begin(), sorted_.end());
        sorted_.erase(it, sorted_.end());

        for (int i = 0; i < sorted_.size(); ++i) {
            value_to_index_[sorted_[i]] = i + 1;
            index_to_value_[i + 1] = sorted_[i];
        }

        for (const auto& value : input) {
            discrete_.emplace_back(value_to_index_[value]);
        }
    }

    std::vector<int> getDiscrete() const {
        return discrete_;
    }

    int toDiscrete(const T& value) const {
        return value_to_index_.at(value);
    }

    T toOriginal(int index) const {
        return index_to_value_.at(index);
    }

private:
    std::vector<T> sorted_;
    std::unordered_map<T, int> value_to_index_;
    std::unordered_map<int, T> index_to_value_;
    std::vector<int> discrete_;
};
