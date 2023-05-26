#include "s21_containers.h"

namespace s21 {

template <class T, class Container = Deque<T>>
class Queue {
 private:
  Container cont;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() {}
  Queue(std::initializer_list<T> const &items) : cont(items) {}

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  size_type size() { return cont.size(); }
  bool empty() { return cont.empty(); }

  void push(const_reference value) { cont.push_back(value); }
  void pop() { cont.pop_front(); }
  void swap(Queue &other) { std::swap(cont, other.cont); }
  template <class... Args>
  void emplace(Args &&...args) {
    cont.emplace_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21