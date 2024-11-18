#include <bits/stdc++.h>

class SuffixArray {
 public:
  SuffixArray(const std::string& s) { BuildSuffixArray(s); }

  const std::vector<int>& GetSuffixArray() const { return suffix_array_; }

 private:
  std::vector<int> suffix_array_;

  void BuildSuffixArray(const std::string& s) {
    int n = s.size();
    suffix_array_.resize(n);
    std::vector<int> temp_sa(n), rank(n), new_rank(n);
    int max_rank = 256;

    for (int i = 0; i < n; ++i) {
      suffix_array_[i] = i;
      rank[i] = s[i];
    }

    for (int length = 1; length < n; length <<= 1) {
      std::vector<int> cnt(std::max(n, max_rank + 1), 0);
      for (int i = 0; i < n; ++i) {
        int key = (suffix_array_[i] + length < n)
                      ? rank[suffix_array_[i] + length]
                      : 0;
        cnt[key]++;
      }
      for (int i = 1; i < cnt.size(); ++i) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
        int key = (suffix_array_[i] + length < n)
                      ? rank[suffix_array_[i] + length]
                      : 0;
        temp_sa[--cnt[key]] = suffix_array_[i];
      }

      cnt.assign(std::max(n, max_rank + 1), 0);
      for (int i = 0; i < n; ++i) {
        int key = rank[temp_sa[i]];
        cnt[key]++;
      }
      for (int i = 1; i < cnt.size(); ++i) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
        int key = rank[temp_sa[i]];
        suffix_array_[--cnt[key]] = temp_sa[i];
      }

      new_rank[suffix_array_[0]] = 0;
      int num_ranks = 1;
      for (int i = 1; i < n; ++i) {
        int a = suffix_array_[i - 1], b = suffix_array_[i];
        int rank_a1 = rank[a];
        int rank_b1 = rank[b];
        int rank_a2 = (a + length < n) ? rank[a + length] : 0;
        int rank_b2 = (b + length < n) ? rank[b + length] : 0;
        if (rank_a1 == rank_b1 && rank_a2 == rank_b2) {
          new_rank[b] = new_rank[a];
        } else {
          new_rank[b] = num_ranks++;
        }
      }

      rank.swap(new_rank);
      if (num_ranks == n)
        break;
      max_rank = num_ranks;
    }
  }
};