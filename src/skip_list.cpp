#include <cmath>
#include <cstring>
#include <optional>
#include <sstream>
#include <vector>
using std::vector;


class skip_list {
  int value;
  vector<skip_list*> next = {nullptr};

  static bool flipCoin() { return rand() % 2; }

  skip_list* _insert(int value, int level = -1) {
    if (level < 0) level = next.size() - 1;
    skip_list* it;
    if (next[level] && next[level]->value < value) it = next[level]->_insert(value, level);
    else if (level == 0) {
      int promotions = 0;
      while (flipCoin()) ++promotions;
      auto* n = new skip_list(value);
      n->next.resize(1 + promotions);
      n->next[0] = next[0];
      next[0] = n;
      it = n;
    }
    else {
      auto iter = _insert(value, level - 1);
      if (level < iter->next.size()) {
        iter->next[level] = next[level];
        next[level] = iter;
      }
      it = iter;
    }

    return it;
  }

  skip_list* _search(int i, int level = -1) {
    if (level < 0) level = next.size() - 1;

    if (next[level] && next[level]->value <= i) return next[level]->_search(i, level);
    else if (level == 0) {
      if (i == value) return this;
      else return nullptr;
    }
    else {
      return _search(i, level - 1);
    }
  }
public:
  skip_list(int i) : value(i) {
  }

  void insert(int value) {
    auto it = _insert(value, -1);
    int current = next.size();
    if(it->next.size() > current) {
      next.resize(it->next.size());
      for (int i = current; i < next.size(); ++i) {
        next[i] = it;
      }
    }
  }

  skip_list* search(int i) {
    return _search(i, -1);
  }

  void printLevel(int level) {
    if (level < next.size())
      printf("%d ", value);
    else {
      std::stringstream s;
      s << value;
      for (int i = 0; i < s.str().size() + 1; ++i) printf(" ");
    }
    if (next[0]) next[0]->printLevel(level);
  }
  void print() {
    for (int i = next.size() - 1; i >= 0; --i) {
      printf("level %d : ", i);
      next[0]->printLevel(i);
      printf("\n");
    }
  }
};

int main () {
  srand(time(NULL));

  skip_list sl(0);
  int num_el = 40;
  for (int i = 0; i < num_el; ++i) sl.insert((rand() % 100) - 50);
  sl.print();
  auto it = sl.search(24);
  if (!it) printf("24 not found\n");
  else printf("Found 24\n");
}
