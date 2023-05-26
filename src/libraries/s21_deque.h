#include "s21_containers.h"

namespace s21 {

template <class T>
class Deque {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  struct node {
    value_type val;
    node *next;
    node *prev;
    node() : val(), next(nullptr), prev(nullptr){};
    node(value_type value) : val(value), next(nullptr), prev(nullptr){};
  };

 public:
  // constructors
  Deque() : head(nullptr), tail(nullptr), deqSize(0U){};
  Deque(std::initializer_list<value_type> const &items) : Deque() {
    for (auto it = items.begin(); it != items.end(); it++) {
      push_back(*it);
    }
  }
  Deque(const Deque &other) : Deque() {
    for (size_type i = 0; i < other.size(); ++i) {
      push_back(other[i]->val);
    }
  }
  Deque(Deque &&other) noexcept : Deque() {
    swap(other);
    other.~Deque();
  }
  ~Deque() {
    deqSize = 0U;
    node *current = head;
    while (current) {
      node *next = current->next;
      delete current;
      current = next;
    }
  }

  Deque &operator=(Deque &&other) {
    swap(other);
    other.~Deque();
    return *this;
  }

  const_reference front() const { return head->val; }
  const_reference back() const { return tail->val; }

  bool empty() const noexcept { return head == nullptr; }
  size_type size() const noexcept { return deqSize; }

  node *operator[](const size_type index) const {
    if (!head) return nullptr;
    node *p = head;
    for (size_type i = 0; i < index; i++) {
      p = p->next;
      if (!p) return nullptr;
    }
    return p;
  }

  void push_back(const_reference val) {
    std::unique_ptr<node> buff(new node(val));
    if (empty()) {
      head = tail = buff.get();
    } else {
      buff->prev = tail;
      tail->next = buff.get();
      tail = buff.get();
    }
    buff.release();
    deqSize++;
  }

  void push_front(value_type val) {
    std::unique_ptr<node> buff(new node(std::move(val)));
    buff->next = head;
    buff->prev = nullptr;
    if (empty()) {
      head = tail = buff.get();
    } else {
      head->prev = buff.get();
      head = buff.get();
    }
    buff.release();
    deqSize++;
  }

  void pop_back() {
    if (empty()) return;
    std::unique_ptr<node> buff(tail);
    if (tail->prev == nullptr) {
      tail = head = nullptr;
    } else {
      tail->prev->next = nullptr;
      tail = tail->prev;
    }
    deqSize--;
  }

  void pop_front() {
    if (empty()) return;
    std::unique_ptr<node> buff(head);
    if (head->next == nullptr) {
      tail = head = nullptr;
    } else {
      head->next->prev = nullptr;
      head = head->next;
    }
    deqSize--;
  }

  void swap(Deque &other) {
    std::swap(other.head, head);
    std::swap(other.tail, tail);
    std::swap(other.deqSize, deqSize);
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    value_type temp_(std::forward<Args>(args)...);
    push_back(temp_);
  }

 private:
  node *head;
  node *tail;

  size_type deqSize;
};
}  // namespace s21