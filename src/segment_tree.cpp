#include <iostream>
#include <vector>

class segmentTree {
  std::vector<int> data;
  const int n;

public:
  segmentTree(std::vector<int>& v) : n(v.size()) {
    // need two n for binary tree of diameter n
    data.resize(n * 2);
   
    for (int i = 0; i < n; ++i) {
      data[n + i] = v[i];
    }

    for (int i = n - 1; i >= 0; --i) {
      data[i] = data[i * 2 + 1];
      if (i * 2 + 2 < 2 * n) data[i] += data[i * 2 + 2];
    }

  }

  int mid (int l, int r) const { return l + (r - l) / 2; }

  int query(int l, int r, int i = 0, int s = 0, int e = -1) {
    if (e == -1) e = n - 1;
    if (s >= l && r >= e) {
      printf("USING SEG: %d to %d = %d\n", s, e, data[i]);
      return data[i];
    } // if the whole interval in contained
    if (s > r || e < l) return 0;
    int midp = mid(s, e);
    return query(l, r, 2 * i + 1, s, midp) + 
           query(l, r, 2 * i + 2, midp + 1, e);
  }

};

int main() {
  std::vector<int> data = {1, 2, 3, 4, 5};
  segmentTree st(data);
  std::cout << st.query(0, 4) << '\n';
  std::cout << st.query(1, 4) << '\n';
  std::cout << st.query(1, 3) << '\n';
}
