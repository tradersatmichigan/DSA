#include <iostream>
#include <memory>
#include <string>

/*
  * a basic dictionary structure that allows for fast 
  * key value look ups. This implementation only allows 
  * lower case string keys.
  */
class trie {
  static const int ALPHABET_SIZE = 26;
  std::unique_ptr<trie> children[ALPHABET_SIZE] = { nullptr };
  int value = 0;
  
public:
  int& operator[](std::string_view key) {
    if (key.empty()) return value;
    int child = key.front() - 'a';

    if (!children[child]) children[child] = std::make_unique<trie>();

    key.remove_prefix(1);
    return (*children[child])[key];
  }
  
};

int main() {
  trie t;

  t["myKey"] = 5;
  std::cout << "Retreiving a value by key : " << t["myKey"] << '\n';

  std::cout << "Accessing a key that hasn't been set : " << t["undefinedKey"] << '\n';
}
