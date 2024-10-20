#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

std::vector<size_t> LPS(const std::string &s) {
  assert(s.size());
  std::vector<size_t> v(s.size());

  v[0] = 0;
  int len = 0;

  for (size_t i = 1; i < s.size(); ++i) {
    while (len > 0 && s[len] != s[i]) len = v[len - 1];

    len += s[len] == s[i];

    v[i] = len;
  }

  return v;
}

size_t find(const std::string &needle, const std::string &haystack) {
  const auto v = LPS(needle);
  
  size_t needle_ptr = 0;

  for (size_t i = 0; i < haystack.size(); ++i) {
    if (haystack[i] != needle[needle_ptr]) {
      if (needle_ptr > 0)
        needle_ptr = v[needle_ptr - 1];
    }
    else {
      ++needle_ptr;
    }

    if (needle_ptr == needle.size()) {
      return 1 + i - needle.size();
    }
  }

  return haystack.size();
}

void test(size_t string_size) {
  const auto gen = []() {
    return (rand() % 26) + 'a';
  };

  std::string haystack(string_size, 0);
  std::generate(haystack.begin(), haystack.end(), gen);

  size_t search_start = rand() % haystack.size();
  size_t search_size = rand() % (haystack.size() - search_start);
  ++search_size;

  std::string needle = haystack.substr(search_start, search_size);
  
  const auto actual = find(needle, haystack);
  const auto expected = haystack.find(needle);

  if (actual != expected) {
    printf("FAILING TEST! %ld != %ld\n", actual, expected);
    std::cout << needle << std::endl;
    std::cout << haystack << std::endl;
  }
  else {
    std::cout << "pass test\n";
  }
}
int main() {
  const int size = 200;
  const int num_test = 50;
  srand(0);

  for (int i = 0; i < num_test; ++i) {
    test(size);
  }
}
