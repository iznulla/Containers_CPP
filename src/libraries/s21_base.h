#ifndef CPP2_S21_CONTAINERS_LIBRARIES_S21_BASE_H_
#define CPP2_S21_CONTAINERS_LIBRARIES_S21_BASE_H_

namespace s21 {
template <typename T>
class s21_base {
 protected:
  s21_base() {}
  T *sequence_;
  size_t s_size_;

 public:
  using pointer = *T;
  using const_pointer = const *T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIBRARIES_S21_BASE_H_