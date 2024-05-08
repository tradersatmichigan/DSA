#include <functional>

template <typename T, typename Comp = std::less<T>>
class splay_tree {
  struct node {
    node *left, *right, *parent;
    T val;

    node(const T& val = T())
        : left(nullptr), right(nullptr), parent(nullptr), val(val) {}
  };

  Comp comp;
  unsigned long size;
  node* root;

  void left_rotate(node* x) {}

  void right_rotate(node* x) {}

  void splay(node* x) {}

  void replace(node* u, node* v) {}

  node* subtree_minimum(node* u) {}

  node* subtree_maximum(node* u) {}

 public:
  splay_tree() : root(nullptr), size(0) {}

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
      root->right = to_insert;
    } else {
      root->left = to_insert;
    }

    splay(to_insert);
    ++size;
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

  void remove(const T& val) {
    node* to_remove = find(val);
    if (to_remove == nullptr) {
      return;
    }

    splay(to_remove);
    // TODO: actually remove to_remove
  }

  const T& minimum() {}

  const T& maximum() {}
};
