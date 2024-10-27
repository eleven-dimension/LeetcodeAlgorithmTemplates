#include <bits/stdc++.h>

template <class T>
class PrefixSum2D {
 public:
  PrefixSum2D(const std::vector<std::vector<T>>& data) {
    int rows = data.size();
    int cols = rows > 0 ? data[0].size() : 0;

    prefix_sums_.assign(rows + 1, std::vector<T>(cols + 1, 0));

    for (int i = 1; i <= rows; ++i) {
      for (int j = 1; j <= cols; ++j) {
        prefix_sums_[i][j] = data[i - 1][j - 1] + prefix_sums_[i - 1][j] +
                             prefix_sums_[i][j - 1] -
                             prefix_sums_[i - 1][j - 1];
      }
    }
  }

  T Sum(int x1, int y1, int x2, int y2) const {
    if (x1 > x2 || y1 > y2 || x2 >= prefix_sums_.size() - 1 ||
        y2 >= prefix_sums_[0].size() - 1) {
      throw std::out_of_range("Invalid range");
    }
    return prefix_sums_[x2 + 1][y2 + 1] - prefix_sums_[x1][y2 + 1] -
           prefix_sums_[x2 + 1][y1] + prefix_sums_[x1][y1];
  }

 private:
  std::vector<std::vector<T>> prefix_sums_;
};

int main() {
  {
    std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    PrefixSum2D<int> ps2d(data);

    int result_1 = ps2d.Sum(0, 0, 1, 1);
    std::cout << "Sum of rectangle (0,0) to (1,1): " << result_1 << std::endl;

    int result_2 = ps2d.Sum(1, 1, 2, 1);
    std::cout << "Sum of rectangle (1,1) to (2,1): " << result_2 << std::endl;

    int result_3 = ps2d.Sum(1, 1, 2, 2);
    std::cout << "Sum of rectangle (1,1) to (2,2): " << result_3 << std::endl;
  }

  {
    std::vector<std::vector<double>> data = {{1.1, 2.2}, {3.3, 4.4}};
    PrefixSum2D<double> ps2d(data);

    double result = ps2d.Sum(0, 0, 1, 1);
    std::cout << "Sum of rectangle (0,0) to (1,1): " << result << std::endl;
  }

  return 0;
}
