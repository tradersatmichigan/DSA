#include <iostream>
template <int i>
struct factorial {
  enum { value = i * factorial<i - 1>::value };
};

template<>
struct factorial<0>
{
  enum { value = 0 };
};

int main() {
  // 150 factorial is calculated at compile time instead of runtime
  std::cout << "150 factorial is : " << factorial<150>::value << '\n';
}
