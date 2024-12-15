#include <bits/stdc++.h>

template <typename T>
concept IsContainer = requires(const T& t) {
  t.begin();
  t.end();
};

template <typename T>
concept Printable = requires(std::ostream& os, const T& t) {
  { os << t } -> std::same_as<std::ostream&>;
} && !std::same_as<T, std::string> && !std::same_as<std::string_view, T>;

template <typename T>
concept UnIterable =
    std::same_as<T, std::stack<typename T::value_type>> ||
    std::same_as<T, std::queue<typename T::value_type>> ||
    std::same_as<T, std::priority_queue<typename T::value_type>>;

void printWithoutEndl(const std::string& s);
void printWithoutEndl(std::string_view s);

template <typename T>
  requires Printable<T>
void printWithoutEndl(const T& element);

template <typename T, size_t N>
void printWithoutEndl(const T (&arr)[N]);

template <typename T>
  requires IsContainer<T>
void printWithoutEndl(const T& container);

template <typename T, typename U>
void printWithoutEndl(const std::pair<T, U>& p);

template <typename T>
  requires UnIterable<T>
void printWithoutEndl(const T& q);

template <std::size_t Index = 0, typename... Args>
void printTupleElements(const std::tuple<Args...>& t);

template <typename... Args>
void printWithoutEndl(const std::tuple<Args...>& t);

template <typename First, typename... Rest>
void printWithoutEndl(const First& first, const Rest&... rest);

template <typename... Args>
void println(const Args&... args);

void printWithoutEndl(const std::string& s) {
  std::cout << "\"" << s << "\"";
}

void printWithoutEndl(std::string_view s) {
  std::cout << "\"" << s << "\"";
}

template <typename T>
  requires Printable<T>
void printWithoutEndl(const T& element) {
  std::cout << element;
}

template <typename T, size_t N>
void printWithoutEndl(const T (&arr)[N]) {
  std::cout << "[";
  bool is_first_element = true;
  for (size_t index = 0; index < N; ++index) {
    if (!is_first_element) {
      std::cout << ", ";
    } else {
      is_first_element = false;
    }
    printWithoutEndl(arr[index]);
  }
  std::cout << "]";
}

template <typename T>
  requires IsContainer<T>
void printWithoutEndl(const T& container) {
  std::cout << "[";
  bool is_first_element = true;
  for (const auto& element : container) {
    if (!is_first_element) {
      std::cout << ", ";
    } else {
      is_first_element = false;
    }
    printWithoutEndl(element);
  }
  std::cout << "]";
}

template <typename T, typename U>
void printWithoutEndl(const std::pair<T, U>& p) {
  std::cout << "(";
  printWithoutEndl(p.first);
  std::cout << ", ";
  printWithoutEndl(p.second);
  std::cout << ")";
}

template <typename T>
  requires UnIterable<T>
void printWithoutEndl(const T& q) {
  std::cout << "[";
  bool is_first_element = true;
  T temp(q);
  while (!temp.empty()) {
    if (!is_first_element) {
      std::cout << ", ";
    } else {
      is_first_element = false;
    }

    if constexpr (std::same_as<T, std::queue<typename T::value_type>>) {
      printWithoutEndl(temp.front());
      temp.pop();
    } else {
      printWithoutEndl(temp.top());
      temp.pop();
    }
  }
  std::cout << "]";
}

template <std::size_t Index, typename... Args>
void printTupleElements(const std::tuple<Args...>& t) {
  if constexpr (Index < sizeof...(Args)) {
    if constexpr (Index != 0) {
      std::cout << ", ";
    }
    printWithoutEndl(std::get<Index>(t));
    printTupleElements<Index + 1>(t);
  }
}

template <typename... Args>
void printWithoutEndl(const std::tuple<Args...>& t) {
  std::cout << "(";
  printTupleElements(t);
  std::cout << ")";
}

template <typename First, typename... Rest>
void printWithoutEndl(const First& first, const Rest&... rest) {
  printWithoutEndl(first);
  if constexpr (sizeof...(Rest) > 0) {
    std::cout << ", ";
    printWithoutEndl(rest...);
  }
}

template <typename... Args>
void println(const Args&... args) {
  printWithoutEndl(args...);
  std::cout << std::endl;
}

int main() {
  {
    std::vector<std::vector<int>> v = {{1, 2}, {3, 4}};
    println(v);
    int x = 10;
    println(x);
  }
  {
    std::set<int> s = {1, 2, 3};
    println(s);
  }
  {
    std::string s = "123, 123";
    println(s);
  }
  {
    std::map<int, std::string> mp = {{1, "1"}, {2, "2"}, {3, "3"}};
    println(mp);
  }
  {
    std::vector<std::string> v = {"123", "345"};
    println(v);
  }

  {
    std::tuple<int, double, std::string> t1 = {0, 0, "zzz"};
    println(t1);

    std::tuple<int, double, std::vector<std::string>> t2 = {0, 0, {"zzz"}};
    println(t2);
  }
  {
    std::bitset<8> bits;
    println(bits);
  }

  {
    std::stack<std::vector<int>> s1;
    s1.push(std::vector<int>{1, 2});
    s1.push(std::vector<int>{7});
    s1.push(std::vector<int>{1, 0});
    println(s1);
  }

  {
    std::unordered_set<int> s = {3, 1, 4, 1, 5, 9};
    println(s);
  }

  {
    int a[] = {1, 2, 3, 4};
    println(a);
  }

  {
    std::queue<int> q;
    q.push(1);
    q.push(3);
    q.push(6);
    println(q);
  }

  {
    std::priority_queue<int> q;
    q.push(1);
    q.push(5);
    q.push(-1);
    println(q);
  }
  {
    std::map<int, std::vector<int>> mp = {{1, std::vector<int>{1, 2, 3}},
                                          {2, std::vector<int>{1, 2, 8}}};
    println(mp);
  }

  {
    int a = 5;
    double b = 3.14;
    std::string c = "Hello";
    println(a, b, c);
  }
}
