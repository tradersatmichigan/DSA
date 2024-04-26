#include <cassert>
#include <iostream>
template<unsigned int size, typename T = unsigned int>
class bit_set {

  T set[size / sizeof(T) + (bool) (size % sizeof(T))];

public:

  void add(unsigned int key) {
    unsigned int index = key / sizeof(T);
    unsigned int offset = key % sizeof(T);
    set[index] |= (1 << offset);
  }

  bool contains(unsigned int key) {
    unsigned int index = key / sizeof(T);
    unsigned int offset = key % sizeof(T);
    return set[index] & (1 << offset);
  }
};

int main () {
  bit_set<100> bs;

  assert(!bs.contains(1));

  bs.add(1);
  assert(bs.contains(1));

  std::cout << "Test pass\n";
}
