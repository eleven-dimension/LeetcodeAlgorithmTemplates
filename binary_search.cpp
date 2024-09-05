#include <algorithm>
#include <iostream>
#include <vector>

// [T, T, T, ..., T, F, F, F, ...]
// find the first position p in [l, r] such that condition(p) is false
#include <ranges>
#include <optional>

template <typename T1, typename T2>
std::optional<int> FirstFalse(T1 l, T2 r, auto condition) {
    static_assert(std::is_integral_v<T1> && std::is_integral_v<T2>, "Both l and r must be integral types");
    int l_int = static_cast<int>(l);
    int r_int = static_cast<int>(r);
    if (r_int < l_int) {
        return std::nullopt;
    }

    auto range = std::views::iota(l_int, r_int + 1);
    auto iter = std::ranges::lower_bound(range, 0, [&](int pos, auto) {
        return condition(pos);
    });
    if (iter != range.end()) {
        return *iter;
    }
    return std::nullopt;
}

template <typename T1, typename T2>
std::optional<int> FirstTrue(T1 l, T2 r, auto condition) {
    static_assert(std::is_integral_v<T1> && std::is_integral_v<T2>, "Both l and r must be integral types");
    int l_int = static_cast<int>(l);
    int r_int = static_cast<int>(r);
    if (r_int < l_int) {
        return std::nullopt;
    }

    auto range = std::views::iota(l_int, r_int + 1);
    auto iter = std::ranges::upper_bound(range, 0, [&](auto, int pos) {
        return condition(pos);
    });
    if (iter != range.end()) {
        return *iter;
    }
    return std::nullopt;
}

using namespace std;
int main() {
    vector<int> f = {1, 2, 3, 4, 6};

    {
        auto result = FirstTrue(0, 4, [&](int pos) { return f[pos] > 3; });
        if (result) {
            cout << *result << endl;
        } else {
            cout << -1 << endl;
        }
    }

    {
        auto result = FirstTrue(0, 4, [&](int pos) { return f[pos] > 10; });
        if (result) {
            cout << *result << endl;
        } else {
            cout << -1 << endl;
        }
    }

    {
        auto result = FirstFalse(0, 4, [&](int pos) { return f[pos] <= 1; });
        if (result) {
            cout << *result << endl;
        } else {
            cout << -1 << endl;
        }
    }

    {
        auto result = FirstFalse(0, 4, [&](int pos) { return f[pos] > 0; });
        if (result) {
            cout << *result << endl;
        } else {
            cout << -1 << endl;
        }
    }
}