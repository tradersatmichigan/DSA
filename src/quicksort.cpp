#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using std::vector;

enum pivot_selector {
  First,
  Random
};

template<class T, int i>
struct Wrapper {
  static T get_pivot(T begin, T end) {
    // overloaded for specific types
  }
};

template<class T>
struct Wrapper<T, First> {
  static T get_pivot(T begin, T end) {
    return begin;
  }
};

template<class T>
struct Wrapper<T, Random> {
  static T get_pivot(T begin, T end) {
    int dist = std::distance(begin, end);
    return begin + (rand() % dist);
  }
};

template<class T, int I>
T get_pivot(T begin, T end) {
  return Wrapper<T, I>::get_pivot(begin, end);
}


template <int I, class T>
void quick_sort(T begin, T end) {
  if (begin == end || begin + 1 == end) return;
  T pivot = get_pivot<T, I>(begin, end);
  std::swap(*pivot, *begin);
  T left = begin + 1;
  for (T i = left; i != end; ++i) {
    if (*begin >= *i) {
      std::swap(*left, *i);
      ++left;
    }
  }
  std::swap(*begin, *(left - 1));

  quick_sort<I>(begin, left - 1);
  quick_sort<I>(left, end);
}

template <class T>
void prettyPrint(vector<T> &v) {
  std::cout << '{';
  for (int i = 0; i < v.size() - 1; ++i) {
    std::cout << v[i] << ", ";
  }
  std::cout << v.back();
  std::cout << "}\n";
}

vector<int> randVec(const int max_size, const int max_val) {
  vector<int> res(max_size);
  auto gen = [max_val]() {return rand() % max_val;};
  std::generate(res.begin(), res.end(), gen);
  return std::move(res);
}

int main() {
  srand(time(NULL));

  const int MAX_SIZE = 30;
  const int MAX_VAL = 200;

  auto v = randVec(MAX_SIZE, MAX_VAL);
  
  std::cout << "Before: ";
  prettyPrint(v);

  // the template parameter determines which pivot selection is used
  // You could also call quick_sort<Random>(...)
  quick_sort<First>(v.begin(), v.end());

  std::cout << "After: ";
  prettyPrint(v);

  return 0;
}
