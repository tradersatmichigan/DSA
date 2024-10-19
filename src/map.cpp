#include <random>
#include <vector>

template<class K, class V>
class Map {
  struct Node {
    K key;
    V val;
    bool empty = true;
  };

  std::vector<Node> tree;

  size_t find(K key) {
    size_t i = 1;
    while (true) {
      if (i >= tree.size()) tree.resize(2 * tree.size());
      if (tree[i].key == key || tree[i].empty) break;
      else if (tree[i].key > key) i = 2 * i;
      else i = 2 * i + 1;
    }
    return i;
  }
public:
  Map() {
    tree.resize(2);
  }
  void insert(K key, V val) {
    auto i = find(key);
    tree[i].key = key;
    tree[i].val = val;
    tree[i].empty = false;
  }

  V get(K key) {
    auto i = find(key);
    assert(!tree[i].empty);

    return tree[i].val;
  }
};

int main() {
  const int MAX = 1000;
  Map<int, int> mp;
  std::vector<int> nums;
  for (int i = 0; i < MAX; ++i) {
    nums.push_back(i);
  }

  std::shuffle(nums.begin(), nums.end(), std::default_random_engine(0));

  for (const auto num : nums) mp.insert(num, num * num);

  for (int i = 0; i < MAX; ++i) {
    if (mp.get(i) != i*i) {
      printf("FAIL TEST %d\n", i);
      printf("Expecting %d, got %d", i * i, mp.get(i));
      exit(1);
    }
  }
  printf("test passed\n");
}
