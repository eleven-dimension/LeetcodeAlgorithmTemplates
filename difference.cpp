#include <bits/stdc++.h>

template <class T>
class DifferenceArray {
 public:
  DifferenceArray(size_t size)
      : data_(size, 0), diff_(size + 1, 0), diff_applied_(true) {}

  DifferenceArray(const std::vector<T>& data)
      : data_(data.begin(), data.end()),
        diff_(data.size() + 1, 0),
        diff_applied_(true) {}

  void Add(size_t left, size_t right, T x) {
    if (left > right || right >= data_.size()) {
      throw std::out_of_range("Invalid range");
    }
    diff_[left] += x;
    diff_[right + 1] -= x;
    diff_applied_ = false;
  }

  const std::vector<T>& GetArray() {
    ApplyDiff();
    return data_;
  }

 private:
  void ApplyDiff() {
    if (diff_applied_)
      return;
    T acc = 0;
    for (size_t i = 0; i < data_.size(); ++i) {
      acc += diff_[i];
      data_[i] += acc;
      diff_[i] = 0;
    }
    diff_[data_.size()] = 0;
    diff_applied_ = true;
  }

  std::vector<T> data_;
  std::vector<T> diff_;
  bool diff_applied_;
};

using namespace std;

int main() {
  DifferenceArray<int> df(5);
  df.Add(0, 1, 3);
  df.Add(1, 3, 2);
  auto v = df.GetArray();
  for (auto& x : v) {
    cout << x << " ";
  }
}