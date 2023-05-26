#ifndef S21_MAP_H
#define S21_MAP_H
#include "tree.h"

namespace s21 {

template <class K, class T>
class map : public Tree<K, T> {
 public:
  using RBT = typename s21::Tree<K, T>;
  using Key = K;
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = size_t;
  using iterator = typename RBT::mapIterator;
  using insert_result = std::pair<iterator, bool>;
  //  using pack_pair = s21::vector<std::pair<iterator, bool>>;

 public:
  map() : RBT(){};

  map(std::initializer_list<value_type> const &items);
  map(const map &m) : RBT(m){};
  map(map &&m) noexcept { *this = std::move(m); }
  ~map() = default;

  map &operator=(map &&m) noexcept;

  bool empty() noexcept { return this->root == nullptr; }
  size_type size() noexcept { return this->tree_size; };
  [[nodiscard]] size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(typename RBT::tnode);
  };

  T &at(const Key &key);
  T &operator[](const Key &key);

  void clear() noexcept;
  insert_result insert(const value_type &value);
  insert_result insert(const K &key, const T &value);
  insert_result insert_or_assign(const K &key, const T &value);
  void erase(iterator pos);
  void swap(map &other) { std::swap(RBT::root, other.root); }
  void merge(map &other);
  bool contains(const key_type &key) {
    return RBT::containsNode(key, RBT::root);
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);

  friend RBT;
};
template <class K, class T>
map<K, T>::map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    RBT::addnode(*i, RBT::root, false);
  }
}
template <class K, class T>
map<K, T> &map<K, T>::operator=(map &&m) noexcept {
  this->root = m.root;
  m.root = nullptr;
  return *this;
}
template <class K, class T>
void map<K, T>::clear() noexcept {
  RBT::destroy(this->root);
  this->root = nullptr;
}
template <class K, class T>
typename map<K, T>::insert_result map<K, T>::insert(
    const map::value_type &value) {
  return RBT::addnode(value, this->root, false);
}
template <class K, class T>
typename map<K, T>::insert_result map<K, T>::insert(const K &key,
                                                    const T &value) {
  value_type x(key, value);
  return RBT::addnode(x, this->root, false);
}
template <class K, class T>
typename map<K, T>::insert_result map<K, T>::insert_or_assign(const K &key,
                                                              const T &value) {
  value_type x(key, value);
  return RBT::addnode(x, this->root, true);
}
template <class K, class T>
void map<K, T>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    RBT::addnode(*it, this->root, false);
  }
}
template <class K, class T>
void map<K, T>::erase(map::iterator pos) {
  typename RBT::tnode *data = RBT::get_current(pos);
  RBT::eraseNode(data);
  --this->tree_size;
}

template <class K, class T>
template <class... Args>
std::vector<std::pair<typename map<K, T>::iterator, bool>> map<K, T>::emplace(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  value_type newArg(std::forward<Args>(args)...);
  result.push_back(insert(newArg));
  return result;
}
template <class K, class T>
T &map<K, T>::at(const K &key) {
  typename RBT::tnode *result = this->find_data_at(key, this->root);
  if (result == nullptr) {
    throw std::out_of_range("map()");
  } else {
    return result->data.second;
  }
}
template <class K, class T>
T &map<K, T>::operator[](const Key &key) {
  typename RBT::tnode *result = this->find_data_at(key, this->root);
  mapped_type add_data{};
  if (result == nullptr) {
    value_type add_node(key, add_data);
    RBT::addnode(add_node, this->root, false);
  }
  result = this->find_data_at(key, this->root);
  return result->data.second;
}
}  // namespace s21

#endif  // S21_MAP_H
