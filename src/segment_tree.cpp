#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
using std::vector;

/*
* Return the next power of 2 that is at least as great as the input
*/
int nextPower2(int size) {
  int power = 1;
  while (power < size)
    power <<= 1;
  return power;
}

class segmentTree {
 vector<int> tree;
  const int width;

  static int leftChild(int node) { return 2 * node; }
  static int rightChild(int node) { return 2 * node + 1; }
  static int parentNode(int node) { return node / 2; }

  int _query(int root, int start, int end, int queryStart, int queryEnd) const {
    if (start > queryEnd || end < queryStart) return 0;
    else if (start >= queryStart && end <= queryEnd) return tree[root]; 
    int elementsPerChild = (end - start) / 2;
    return _query(leftChild(root), start, start + elementsPerChild, queryStart, queryEnd) + 
           _query(rightChild(root), end - elementsPerChild, end, queryStart, queryEnd);
  }


public:
  segmentTree(vector<int>& data) : width(nextPower2(data.size())) {
    int size = 2 * width;
    tree.resize(size);

    // load in the base data
    auto treePtr = tree.begin() + width;
    for (auto dataPtr = data.begin(); dataPtr != data.end(); ++dataPtr, ++treePtr) {
      *treePtr = *dataPtr;
    }
    // consolidate the numbers into sums
    for (int node = tree.size() / 2; node > 0; --node) {
      tree[node] = tree[leftChild(node)] + tree[rightChild(node)];
    }
  }

  int query(int l, int r) {
    return _query(1, 0, width, l, r);
  }

  void updateElt(int index, int newValue) {
    index += width;
    int delta = newValue - tree[index];
    while (index > 0) {
      tree[index] += delta;
      index = parentNode(index);
    }
  }
};

void test(segmentTree & st, vector<int> &data, int l, int r) {
  static int testNum = 1;
  int actual = std::accumulate(data.begin() + l, data.begin() + r, 0);
  int observed = st.query(l, r);
  if (actual == observed) {
    std::cout << "Test num " << testNum << " passed\n";
  }
  else {
    std::cout << "FAILED TEST " << testNum << '\n'; 
    std::cout << "EXPECTED: " << actual << " GOT: " << observed << '\n';
  }
  ++testNum;
}

int main() {
  vector<int> data = {0, 1, 2, 3, 4, 5, 6};
  segmentTree st(data);

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);

  st.updateElt(1, 10);
  // syncing the vector to match the segment tree
  data[1] = 10;

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);
}
