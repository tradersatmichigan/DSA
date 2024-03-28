#include <vector>

template<typename T>
class decomposition {
  std::vector<T> data;
  std::vector<T> compressed;

public:
  decomposition<T>(std::vector<T>&& _data) {
    data = _data;
  };
};

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  decomposition<int> d(std::move(v));
}
