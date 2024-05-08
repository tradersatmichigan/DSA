#include <cassert>

/*
* A macro to yield the size of a type in bits
* Notice that sizeof returns the size in bytes
*/
#define bitSize(T) 8 * sizeof(T)

/*
  * bit_set is a highly memory efficient set implementation
  * that uses one bit per potential key. Therefore, we can
  * represent a set of size 800 with only around 100 bytes.
  */
typedef unsigned int UI;
template <UI size, typename T = unsigned int>
class bit_set {
  // create an array of size ceil(size / typesize)
  // essentially using as few bits as possible
  T set[size / bitSize(T) + (bool)(size % bitSize(T))];

 public:
  void add(UI key) {
    UI index = key / bitSize(T);
    UI offset = key % bitSize(T);
    set[index] |= ((T)1 << offset);
  }

  bool contains(UI key) {
    UI index = key / bitSize(T);
    UI offset = key % bitSize(T);
    return set[index] & ((T)1 << offset);
  }
};

int main() {
  bit_set<1000> bs;

  assert(!bs.contains(3));

  bs.add(3);
  assert(bs.contains(3));
  assert(!bs.contains(4));

  bs.add(977);
  assert(bs.contains(977));
}
