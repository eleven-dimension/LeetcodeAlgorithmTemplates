#include <bits/stdc++.h>

struct StopWatch {
    StopWatch() : start_time_(std::chrono::system_clock::now()) {}

    ~StopWatch() {
        const auto end_time = std::chrono::system_clock::now();
        const auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_);
        std::cout << duration.count() << "us\n";
    }

private:
    std::chrono::time_point<std::chrono::system_clock> start_time_;
};

template <class T>
size_t HashCombine(size_t seed, const T& value) {
    return seed ^ (std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

template <class... Types>
struct TupleHash {
    size_t operator()(const std::tuple<Types...>& tuple) const {
        size_t res = 0;
        std::apply([&res](const auto&... args) { ((res = HashCombine(res, args)), ...); }, tuple);
        return res;
    }
};

template <class>
class Cache {};

template <class R, class... Args>
class Cache<R(Args...)> {
    using This = Cache<R(Args...)>;

public:
    Cache(auto func) : func_(func) {}

    const auto& operator()(const auto&... args) {
        const auto args_tuple = std::make_tuple(args...);
        auto iter = value_map_.find(args_tuple);
        if (iter != value_map_.end()) {
            return iter->second;
        }
        return value_map_.emplace(args_tuple, func_(*this, args...)).first->second;
    }

private:
    std::function<R(This&, Args...)> func_;

    std::unordered_map<std::tuple<Args...>, R, TupleHash<Args...>> value_map_;
};

int main() {
    constexpr int kN = 10000;
    {
        StopWatch stop_watch;
        std::cout << "Cache decorator: ";
        auto f = Cache<int(int)>([](auto& self, int x) -> int {
            if (x <= 2) {
                return 1;
            }
            return self(x - 1) + self(x - 2);
        });
        f(kN);
    }
    {
        StopWatch stop_watch;

        std::cout << "Simple iteration: ";
        []() {
            int f[kN + 1]{};
            f[1] = 1;
            f[2] = 1;
            for (int i = 3; i <= kN; ++i) {
                f[i] = f[i - 1] + f[i - 2];
            }
            return f[kN];
        }();
    }
}
