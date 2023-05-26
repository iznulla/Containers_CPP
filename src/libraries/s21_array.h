#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include "s21_containers.h"

namespace s21 {

template <typename T, std::size_t N>
class Array {
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;
  // public methods
 public:
  Array() {}

  Array(std::initializer_list<value_type> const &items) {
    size_type i = 0;
    for (auto const &it : items) {
      arr[i++] = it;
    }
  };

  Array(const Array &v) : Array() {
    for (size_type i = 0; i < N; ++i) {
      arr[i] = v.arr[i];
    }
  };

  Array(Array &&v) : Array(v) { v.~Array(); };

  Array operator=(Array &&v) {
    for (size_type i = 0; i < v.size(); ++i) {
      arr[i] = v.arr[i];
    }
    return *this;
  }

  // destructor
  ~Array() {
    for (size_type i = 0; i < size(); ++i) {
      arr[i].~value_type();
    }
  }

  constexpr bool empty() noexcept { return N == 0; }
  constexpr size_type size() noexcept { return N; };
  constexpr size_type max_size() noexcept { return N; }

  reference at(size_type i) {
    if (i >= N) {
      throw std::out_of_range("Incorrect input, no index");
    }
    return arr[i];
  }
  reference operator[](size_type i) { return arr[i]; }

  const_reference front() const { return arr[0]; }
  const_reference back() const { return arr[N - 1]; }

  iterator data() noexcept { return arr; }
  iterator begin() noexcept { return arr; }

  iterator end() noexcept { return arr + size(); }

  void swap(Array &o) noexcept { std::swap(this->arr, o.arr); }
  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

 private:
  value_type arr[N];
};
}  // namespace s21

#endif
