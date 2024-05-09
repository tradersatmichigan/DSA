#include <utility>
#include <vector>
using std::vector;

template<class T, int i>
struct Wrapper {
  static T get_pivot(T begin, T end) {

  }
};

template<class T>
struct Wrapper<T, 1> {
  static T get_pivot(T begin, T end) {
    return begin;
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

int main() {
  vector<int> v = {4, 1, 3, 35, 324, 2, -1};
  quick_sort<1>(v.begin(), v.end());

  printf("{ ");
  for (const auto num : v) printf("%d, ", num);
  printf("}\n");
  return 0;
}
