#include "s21_containers.h"

namespace s21 {

template <class T, class Container = Deque<T>>
class Stack {
 private:
  Container cont;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() {}

  Stack(std::initializer_list<T> const &items) : cont(items) {}

  const_reference top() { return cont.back(); }

  size_type size() { return cont.size(); }
  bool empty() { return cont.empty(); }

  void push(const_reference value) { cont.push_back(value); }
  void pop() { cont.pop_back(); }
  void swap(Stack &other) { std::swap(cont, other.cont); }
  template <class... Args>
  void emplace(Args &&...args) {
    cont.emplace_back(std::forward<Args>(args)...);
  }
};

}  // namespace s21