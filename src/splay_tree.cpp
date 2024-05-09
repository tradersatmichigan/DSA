#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T, typename Comp = std::less<T>>
class splay_tree {
  struct node {
    node *left, *right, *parent;
    T val;

    node(const T& val = T())
        : left(nullptr), right(nullptr), parent(nullptr), val(val) {}
  };

  Comp comp;
  unsigned long _size;
  node* root;

  void left_rotate(node* x) {
    node* y = x->right;
    if (y != nullptr) {
      // Link y's old left to be x's new right
      x->right = y->left;
      if (y->left) {
        y->left->parent = x;
      }
      y->parent = x->parent;
    }

    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    if (y != nullptr) {
      y->left = x;
    }
    x->parent = y;
  }

  void right_rotate(node* x) {
    node* y = x->left;
    if (y != nullptr) {
      x->left = y->right;
      if (y->right) {
        y->right->parent = x;
      }
      y->parent = x->parent;
    }

    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    if (y != nullptr) {
      y->right = x;
    }
    x->parent = y;
  }

  void splay(node* x) {
    while (x->parent != nullptr) {
      if (x->parent->parent == nullptr) {
        // x's parent is the root
        if (x->parent->left == x) {
          right_rotate(x->parent);
        } else {
          left_rotate(x->parent);
        }
      } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
        // x is the left-left grandchild
        right_rotate(x->parent->parent);
        right_rotate(x->parent);
      } else if (x->parent->right == x &&
                 x->parent->parent->right == x->parent) {
        // x is the right-right grandchild
        left_rotate(x->parent->parent);
        left_rotate(x->parent);
      } else if (x->parent->left == x &&
                 x->parent->parent->right == x->parent) {
        // x is the left-right grandchild
        right_rotate(x->parent);
        left_rotate(x->parent);
      } else {
        // x is the right-left grandchild
        left_rotate(x->parent);
        right_rotate(x->parent);
      }
    }
  }

  void replace(node* old, node* sub) {
    if (old->parent == nullptr) {
      root = sub;
    } else if (old == old->parent->left) {
      old->parent->left = sub;
    } else {
      old->parent->right = sub;
    }
    if (sub != nullptr) {
      sub->parent = old->parent;
    }
  }

  node* subtree_minimum(node* u) {
    if (u == nullptr) {
      return nullptr;
    }
    while (u->left != nullptr) {
      u = u->left;
    }
    return u;
  }

  node* subtree_maximum(node* u) {
    if (u == nullptr) {
      return nullptr;
    }
    while (u->right != nullptr) {
      u = u->right;
    }
    return u;
  }

 public:
  splay_tree() : root(nullptr), _size(0) {}

  template <class InputIt>
  splay_tree(InputIt first, InputIt last) : root(nullptr), _size(0) {
    for (InputIt iter = first; iter != last; ++iter) {
      insert(*iter);
    }
  }

  void insert(const T& val) {
    node* to_insert = root;
    node* parent = nullptr;

    while (to_insert != nullptr) {
      parent = to_insert;
      if (comp(to_insert->val, val)) {
        to_insert = to_insert->right;
      } else {
        to_insert = to_insert->left;
      }
    }

    to_insert = new node(val);
    to_insert->parent = parent;

    if (parent == nullptr) {
      root = to_insert;
    } else if (comp(parent->val, to_insert->val)) {
      parent->right = to_insert;
    } else {
      parent->left = to_insert;
    }

    splay(to_insert);
    _size++;
  }

  node* find(const T& val) {
    node* target = root;

    while (target != nullptr) {
      if (comp(target->val, val)) {
        target = target->right;
      } else if (comp(val, target->val)) {
        target = target->left;
      } else {
        splay(target);
        return target;
      }
    }

    return nullptr;
  }

  bool contains(const T& val) { return find(val) != nullptr; }

  void remove(const T& val) {
    node* to_remove = find(val);
    if (!to_remove)
      return;

    splay(to_remove);

    // If to_remove has an empty left or right subtree, then replace
    // with the other subtree.
    if (to_remove->left == nullptr) {
      replace(to_remove, to_remove->right);
    } else if (to_remove->right == nullptr) {
      replace(to_remove, to_remove->left);
    } else {
      // If to_remove has two non-empty subtree, we first must replace
      // it with its in-order successor
      node* successor = subtree_minimum(to_remove->right);
      if (successor->parent != to_remove) {
        replace(successor, successor->right);
        successor->right = to_remove->right;
        successor->right->parent = successor;
      }
      replace(to_remove, successor);
      successor->left = to_remove->left;
      successor->left->parent = successor;
    }

    delete to_remove;
    _size--;
  }

  const T& minimum() const { return subtree_minimum(root)->val; }

  const T& maximum() const { return subtree_maxinimum(root)->val; }

  bool empty() const { return root == nullptr; }

  unsigned long size() const { return _size; }

  const T& root_val() const { return root->val; }

  void print() { print("", root, false, true); }

  void print(const string& prefix, node* parent, bool isLeft, bool isRoot) {
    if (parent == nullptr)
      return;

    if (isRoot) {
      cout << "─────";
    } else {
      cout << prefix << (isLeft ? "L├────" : "R└───");
    }
    cout << parent->val << endl;

    print(prefix + (isLeft ? " │   " : "    "), parent->left, true, false);
    print(prefix + (isLeft ? " │   " : "    "), parent->right, false, false);
  }
};

void simple_test() {
  vector<int> data = {0, 1, 2, 3, 4, 5, 6};
  splay_tree<int> tree(data.begin(), data.end());
  cout << "Initial tree:" << endl;
  tree.print();
  cout << "Search for 0:" << endl;
  assert(tree.contains(0));
  tree.print();
  cout << "Search for 3:" << endl;
  assert(tree.contains(3));
  tree.print();
  cout << "Search for 3 again:" << endl;
  assert(tree.contains(3));
  tree.print();
  cout << "Insert 7:" << endl;
  tree.insert(7);
  tree.print();
}

void timed_test() {
  vector<int> data(10000000);
  iota(data.begin(), data.end(), 1);
  std::random_device rd;
  std::mt19937 g(rd());
  shuffle(data.begin(), data.end(), g);
  splay_tree<int> tree(data.begin(), data.end());

  std::clock_t c_start = std::clock();
  assert(tree.contains(500000));
  std::clock_t c_end = std::clock();

  std::cout << "First search: " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC
            << "ms\n";

  c_start = std::clock();
  assert(tree.contains(500000));
  c_end = std::clock();

  std::cout << "Second search: " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC
            << "ms\n";
}

int main() {
  timed_test();
}
