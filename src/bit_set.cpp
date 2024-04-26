#include <cassert>
#include <iostream>
template<class S, S size, typename T = unsigned int>
class bit_set {

  T set[size / sizeof(T) + (bool) (size % sizeof(T))];

public:
  
  void add(S key) {
    S index = key / sizeof(T);
    S offset = key % sizeof(T);
    set[index] |= ((T)1 << offset);
  }

  bool contains(S key) {
    S index = key / sizeof(T);
    S offset = key % sizeof(T);
    return set[index] & ((T)1 << offset);
  }
};

int main () {
  bit_set<int, 100> bs;

  assert(!bs.contains(1));

  bs.add(1);
  assert(bs.contains(1));

  std::cout << "Test pass\n";
}
