#include <iostream>
#define bitSize(T) 8 * sizeof(T)

typedef unsigned int UI;
template<UI size, typename T = unsigned int>
class bit_set {
  T set[size / bitSize(T) + (bool) (size % bitSize(T))];

public:

  void add(UI key) {
    UI index = key / bitSize(T);
    UI offset = key % bitSize(T);
    set[index] |= ((T)1 << offset);
  }

  bool contains(unsigned int key) {
    UI index = key / bitSize(T);
    UI offset = key % bitSize(T);
    return set[index] & ((T)1 << offset);
  }
};

int main() {
  bit_set<1000> bs;

  bs.add(3);
  bs.contains(3);
}
