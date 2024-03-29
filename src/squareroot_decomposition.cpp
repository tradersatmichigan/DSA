#include <cmath>
#include <iostream>
#include <vector>

/*    Helper class to allow for intuitive access to the array
  *   
  *   Instead of: 
  *     decomposition.update(index, value)
  *   We can now do: 
  *     decomposition[index] = value
  *
  *   We can also use the operator like it returns the value at an index 
  *   Thanks to the over load of operator int() 
  *   ie : 
  *     int result = decomposition[5] + 6;
  *
  */
class paired_int {
  int& base;
  int& derivative;

public:
  paired_int(int& _base, int& _der) : derivative(_der), base(_base) {};

  void operator=(int val) {
    int dif = val - base;
    derivative += dif;
    base += dif;
  }

  operator int() const { return base; }
};

class decomposition {
  std::vector<int> data;
  std::vector<int> compressed;
  int n;

public:
  /*    Note the &&. This is an Rvalue.
   *    Essencially this means we "move" the vector 
   *    instead of making a copy of it, making this 
   *    much more efficient
   */   
  decomposition(std::vector<int>&& _data) {
    data = _data;
    compressed = std::vector<int>(n);
    n = std::ceil(std::sqrt(data.size()));

    for (int b = 0; b < n; ++b) {
      for (int o = 0; o < n; ++o) {
        int i = b * n + o;
        if (i < data.size()) compressed[b] += data[i];
      }
    }
  };

  int query(int l, int r) {
    int sb = l / n;
    int so = l - n * sb;

    int eb = r / n; 
    int eo = r - eb * n;

    int result {0};

    for (int i = sb; i <= eb; ++i) result += compressed[i];

    // subtract head 
    for (int i = 0; i < so; ++i) result -= data[sb * n + i];
    // subtract tail
    int s_end = eb * n + eo + 1;
    int b_end = std::min(eb * n + n, (int)data.size());
    for (; s_end < b_end; ++s_end) result -= data[s_end];

    return result;
  }

  paired_int operator[](int i) {
    return paired_int(data[i], compressed[i / n]);
  }
};

/*
*   Helper test function to allow for a minimal testing suite
*/
void test(int l, int r, decomposition& d, int expected) {
  static int test_num = 1;
  int res = d.query(l, r);
  if (expected != res) {
    std::cout << "TEST " << test_num << " FAILED: expected " << expected << " but got " << res << '\n';
  }
  else {
    std::cout << "test " << test_num << " passed\n";
  }
  ++test_num;
}

/*
*   A very small and non-comprehensive test suite to 
*   demonstrate usage of the decomposition class
*/
int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  decomposition d(std::move(v));
  
  test(0, 5, d, 15);
  test(1, 5, d, 14);
  test(0, 3, d, 10);

  d[2] = 10;
  // d = {1, 2, 10, 4, 5}

  test(0, 5, d, 22);
  test(1, 5, d, 21);
  test(3, 5, d, 9);
}
