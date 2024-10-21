#include <bits/stdc++.h>

enum class HashType { ONE_WAY, TWO_WAY };

class StringHash {
 public:
  StringHash(const std::string& str, unsigned long long mod_1 = 1'000'000'007,
             unsigned long long mod_2 = 1'000'000'009,
             HashType type = HashType::ONE_WAY)
      : n_(str.size()), mod_1_(mod_1), mod_2_(mod_2), hash_type_(type) {
    s_ = "$" + str;
    forward_hash_1_.resize(n_ + 1);
    forward_hash_2_.resize(n_ + 1);
    base_power_mod_1_.resize(n_ + 1);
    base_power_mod_2_.resize(n_ + 1);

    if (hash_type_ == HashType::TWO_WAY) {
      reverse_hash_1_.resize(n_ + 2);
      reverse_hash_2_.resize(n_ + 2);
    }

    CalculatePrefix();
  }

  bool AreSubstringsEqual(int l1, int r1, int l2, int r2) const {
    return GetHash(l1, r1) == GetHash(l2, r2);
  }

  bool IsPalindrome(int l, int r) const {
    if (hash_type_ == HashType::ONE_WAY) {
      throw std::logic_error("Palindrome check requires two-way hash type.");
    }
    return GetHash(l, r) == GetReverseHash(l, r);
  }

  std::pair<unsigned long long, unsigned long long> GetHash(int l,
                                                            int r) const {
    unsigned long long hash1 =
        (forward_hash_1_[r] -
         forward_hash_1_[l - 1] * base_power_mod_1_[r - l + 1] % mod_1_ +
         mod_1_) %
        mod_1_;
    unsigned long long hash2 =
        (forward_hash_2_[r] -
         forward_hash_2_[l - 1] * base_power_mod_2_[r - l + 1] % mod_2_ +
         mod_2_) %
        mod_2_;
    return {hash1, hash2};
  }

  std::pair<unsigned long long, unsigned long long> GetReverseHash(
      int l, int r) const {
    if (hash_type_ == HashType::ONE_WAY) {
      throw std::logic_error(
          "Reverse hash is not available for one-way hash type.");
    }

    unsigned long long hash1 =
        (reverse_hash_1_[l] -
         reverse_hash_1_[r + 1] * base_power_mod_1_[r - l + 1] % mod_1_ +
         mod_1_) %
        mod_1_;
    unsigned long long hash2 =
        (reverse_hash_2_[l] -
         reverse_hash_2_[r + 1] * base_power_mod_2_[r - l + 1] % mod_2_ +
         mod_2_) %
        mod_2_;

    return {hash1, hash2};
  }

 private:
  int n_;
  std::string s_;
  unsigned long long mod_1_, mod_2_;
  const unsigned long long kBase = 131;
  HashType hash_type_;

  std::vector<unsigned long long> forward_hash_1_, forward_hash_2_,
      base_power_mod_1_, base_power_mod_2_;
  std::vector<unsigned long long> reverse_hash_1_, reverse_hash_2_;

  void CalculatePrefix() {
    base_power_mod_1_[0] = base_power_mod_2_[0] = 1;

    for (int i = 1; i <= n_; ++i) {
      forward_hash_1_[i] = (forward_hash_1_[i - 1] * kBase + s_[i]) % mod_1_;
      forward_hash_2_[i] = (forward_hash_2_[i - 1] * kBase + s_[i]) % mod_2_;
      base_power_mod_1_[i] = base_power_mod_1_[i - 1] * kBase % mod_1_;
      base_power_mod_2_[i] = base_power_mod_2_[i - 1] * kBase % mod_2_;
    }

    if (hash_type_ == HashType::TWO_WAY) {
      reverse_hash_1_[n_ + 1] = reverse_hash_2_[n_ + 1] = 0;

      for (int i = n_; i >= 1; --i) {
        reverse_hash_1_[i] = (reverse_hash_1_[i + 1] * kBase + s_[i]) % mod_1_;
        reverse_hash_2_[i] = (reverse_hash_2_[i + 1] * kBase + s_[i]) % mod_2_;
      }
    }
  }
};