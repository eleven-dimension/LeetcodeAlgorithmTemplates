#include <bits/stdc++.h>

template <class T>
T FastPow(T base, size_t exponent, const T& one = 1) {
    T res{one};
    for (; exponent > 0; exponent /= 2) {
        if (exponent % 2) {
            res *= base;
        }
        base *= base;
    }
    return res;
}

template <class T>
struct BiggerInteger {
    using Type = __int128_t;
};

template <>
struct BiggerInteger<int32_t> {
    using Type = int64_t;
};

template <auto Mod, class T = decltype(Mod), bool Safer = true>
class ModInteger final {
    static_assert(Mod > 0);

public:
    using Type = ModInteger<Mod, T>;
    using BiggerType = ModInteger<Mod, typename BiggerInteger<T>::Type>;

    constexpr ModInteger(T val = 0) : val_(val) {
        TuneValue();
    }

    constexpr ModInteger(const Type& mod_value) : val_(mod_value.val_) {}

    template <class U>
    constexpr ModInteger(ModInteger<Mod, U> mod_value) : ModInteger(mod_value.val()) {}

    constexpr Type& operator=(Type rhs) {
        this->val_ = rhs.val_;
        return *this;
    }

    constexpr void TuneValue() {
        while (val_ < 0) {
            val_ += kMaxMultiple;
        }
        if (val_ >= Mod) {
            val_ %= Mod;
        }
    }

    constexpr T val() const {
        return val_;
    }

    constexpr Type operator+(const Type& rhs) const {
        return val_ + rhs.val_;
    }

    constexpr Type operator-(const Type& rhs) const {
        return val_ - rhs.val_;
    }

    constexpr Type operator*(const Type& rhs) const {
        if constexpr (Safer) {
            if (rhs.val_ != 0 && val_ < std::numeric_limits<T>::max() / rhs.val_) {
                return val_ * rhs.val_;
            }
            return BiggerType(val_) * BiggerType(rhs.val_);
        } else {
            return val_ * rhs.val_;
        }
    }

    constexpr Type operator/(const Type& rhs) const {
        return *this * (rhs ^ (Mod - 2));
    }

    constexpr Type operator^(size_t exponent) const {
        return FastPow(*this, exponent);
    }

    constexpr Type& operator+=(const Type& rhs) {
        return *this = *this + rhs;
    }

    constexpr Type& operator-=(const Type& rhs) {
        return *this = *this - rhs;
    }

    constexpr Type& operator*=(const Type& rhs) {
        return *this = *this * rhs;
    }

    constexpr Type& operator/=(const Type& rhs) {
        return *this = *this / rhs;
    }

    constexpr Type& operator^=(const Type& rhs) {
        return *this = *this ^ rhs;
    }

    template <class OStream>
    friend OStream& operator<<(OStream& output_stream, const Type& mod_value) {
        return output_stream << mod_value.val_;
    }

private:
    static constexpr T kMaxMultiple = std::numeric_limits<T>::max() / Mod * Mod;

    T val_ = 0;
};

int main() {
    { std::cout << "7 mod 3 is " << ModInteger<3>(7) << std::endl; }

    {
        using Mod3 = ModInteger<3>;
        std::cout << "(7 + 4) mod 3 is " << Mod3(7) + Mod3(4) << std::endl;
    }

    {
        std::cout << "(1000000006 * 3) mod 1000000007 is:\n";

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
        std::cout << "Overflow: " << 1000000006 * 3 % 1000000007 << std::endl;
#pragma GCC diagnostic pop

        using ModBig = ModInteger<1000000007>;
        std::cout << "No overflow and more simple: " << ModBig(1000000006) * 3 << std::endl;
    }

    {
        using ModBig = ModInteger<1000000007>;
        std::cout << "(2 ^ 10000) % (10 ^ 9 + 7) is " << (ModBig(2) ^ 10000) << std::endl;
    }
}
