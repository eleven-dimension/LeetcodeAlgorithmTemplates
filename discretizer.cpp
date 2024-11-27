#include <bits/stdc++.h>

template <typename T>
class Discretizer {
 public:
  Discretizer(const std::vector<T>& input) {
    sorted_ = input;
    std::sort(sorted_.begin(), sorted_.end());
    sorted_.erase(std::unique(sorted_.begin(), sorted_.end()), sorted_.end());

    value_to_index_.reserve(sorted_.size());
    for (size_t i = 0; i < sorted_.size(); i++) {
      value_to_index_[sorted_[i]] = i;
    }

    discrete_.reserve(input.size());
    for (const auto& value : input) {
      discrete_.emplace_back(value_to_index_[value]);
    }
  }

  const std::vector<int>& GetDiscrete() const { return discrete_; }

  int ToDiscrete(const T& value) const { return value_to_index_.at(value); }

  const T& ToOriginal(int index) const { return sorted_.at(index); }

 private:
  std::vector<T> sorted_;
  std::unordered_map<T, int> value_to_index_;
  std::vector<int> discrete_;
};
