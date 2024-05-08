#include <iostream>
template <int i>
struct factorial {
  enum { value = i * factorial<i - 1>::value };
};

template <>
struct factorial<0> {
  enum { value = 0 };
};

int main() {
  // 150 factorial is calculated at compile time instead of runtime
  // We can use template meta programing to calculate a lot of things
  // at compile time but it will be very gross and unreadable.
  // In modern cpp, we avoid TMP because it isnt necessary
  // with the addition of constexpr and consteval
  std::cout << "150 factorial is : " << factorial<150>::value << '\n';
}
