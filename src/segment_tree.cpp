#include <iostream>
#include <numeric>
#include <vector>
using std::vector;

class segment_tree {
  vector<int> tree;
  const int N;

 public:
  segment_tree(const vector<int>& data) : N(data.size()) {
    tree.resize(N << 1);

    // load in the base data
    for (size_t i = 0; i < N; ++i) {
      tree[N + i] = data[i];
    }

    // Build tree
    for (size_t i = N - 1; i > 0; --i) {
      tree[i] = tree[i << 1] + tree[(i << 1) + 1];
    }
  }

  int query(int l, int r) const {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l % 2) res += tree[l++];
      if (r % 2) res += tree[--r];
    }
    return res;
  }

  void update_elt(int index, int newValue) {
    index += N;
    int delta = newValue - tree[index];
    while (index > 0) {
      tree[index] += delta;
      index >>= 1;
    }
  }
};

void test(segment_tree& st, vector<int>& data, int l, int r) {
  static int testNum = 1;
  int actual = std::accumulate(data.begin() + l, data.begin() + r, 0);
  int observed = st.query(l, r);
  if (actual == observed) {
    std::cout << "Test num " << testNum << " passed\n";
  } else {
    std::cout << "FAILED TEST " << testNum << '\n';
    std::cout << "EXPECTED: " << actual << " GOT: " << observed << '\n';
  }
  ++testNum;
}

int main() {
  vector<int> data = {0, 1, 2, 3, 4, 5, 6};
  segment_tree st(data);

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);

  st.update_elt(1, 10);
  // syncing the vector to match the segment tree
  data[1] = 10;

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);
}
