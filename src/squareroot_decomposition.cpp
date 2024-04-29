#include <cmath>
#include <iostream>
#include <numeric>
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

/*
 * Main class implementation that is constructed by moving a vector ie:
 * vector<int> v = {1, 2, 3, 4};
 * decomposition d(std::move(v));
 *
 * Allows for O(sqrt(n)) sum queries and O(1) update time ie:
 *
 * int res = d.query(1, 5); // return the sum of indicies 1 - 5 (inclusive)
 * d[2] = 10; // update the value of index 2 to 10
 *
 */
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
    n = std::ceil(std::sqrt(data.size()));
    compressed.resize(n);

    for (int block = 0; block < n; ++block) {
      for (int offset = 0; offset < n; ++offset) {
        int index = block * n + offset;
        if (index < data.size()) compressed[block] += data[index];
      }
    }
  };

  int query(int l, int r) {
    int start_block = l / n;
    int start_offset = l - n * start_block;

    int end_block = r / n; 
    int end_offset = r - end_block * n;

    int result {0};

    for (int i = start_block; i <= end_block; ++i) result += compressed[i];

    // subtract head 
    for (int i = 0; i < start_offset; ++i) result -= data[start_block * n + i];

    // subtract tail
    for (int i = end_offset + 1; (i < n) && (data.size() > end_block * n + i); ++i) result -= data[end_block * n + i];

    return result;
  }

  paired_int operator[](int i) {
    return paired_int(data[i], compressed[i / n]);
  }
};

/*
*   Helper test function to allow for a minimal testing suite
*/
void test(int l, int r, decomposition& d, std::vector<int> &v) {
  static int test_num = 1;
  int res = d.query(l, r);
  int expected = std::accumulate(v.begin() + l, v.begin() + r + 1, 0);
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
  std::vector<int> temp = {10, 1, 4, 100, 23, 5, -1, 5, 97, 52};
  std::vector<int> v = temp;
  decomposition d(std::move(temp));
  
  test(0, 5, d, v);
  test(1, 5, d, v);
  test(0, 3, d, v);

  // Changing V so that the test function can calculate the sum correctly
  d[2] = 10;
  v[2] = 10;

  test(0, 5, d, v);
  test(1, 5, d, v);
  test(3, 5, d, v);

  // i = 10; indexable as a normal vector
  int i = d[2];
  std::cout << "d[2] = " << i << '\n';
}
