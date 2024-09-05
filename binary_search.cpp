#include <algorithm>
#include <iostream>
#include <vector>

// [T, T, T, ..., T, F, F, F, ...]
// find the first position p in [l, r] such that condition(p) is false
#include <ranges>
#include <optional>

template <typename T>
std::optional<T> FirstFalse(T l, T r, auto condition) {
    auto range = std::views::iota(l, r + 1);
    auto iter = std::ranges::lower_bound(range, 0, [&](int pos, auto) {
        return condition(pos);
    });
    if (iter != range.end()) {
        return *iter;
    }
    return std::nullopt;
}

template <typename T>
std::optional<T> FirstTrue(T l, T r, auto condition) {
    auto range = std::views::iota(l, r + 1);
    auto iter = std::ranges::upper_bound(range, 0, [&](int pos, auto) {
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
    auto result = FirstTrue(0, 5, [&](int pos) { return f[pos] > 10; });
    if (result) {
        cout << *result << endl;
    } else {
        cout << -1 << endl;
    }
}