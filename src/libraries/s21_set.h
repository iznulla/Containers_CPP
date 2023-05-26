#ifndef S21_SET_H
#define S21_SET_H
#include "tree.h"

namespace s21 {

template <class Key, class T = int>
class set : public Tree<Key, T> {
 public:
  using RBT = typename s21::Tree<Key, T>;
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using iterator = typename RBT::mapIterator;
  using insert_result = std::pair<iterator, bool>;

  set() : RBT(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &s) : RBT(s){};
  set(set &&s) noexcept { *this = std::move(s); }
  ~set() = default;

  set &operator=(set &&s) noexcept;

  bool empty() { return this->root == nullptr; }
  size_type size() { return this->tree_size; };
  [[nodiscard]] size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(typename RBT::tnode) /
           2U;
  };

  void clear() noexcept;
  insert_result insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  iterator find(const Key &key);
  bool contains(const key_type &key) {
    return RBT::containsNode(key, this->root);
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};
template <class Key, class T>
set<Key, T>::set(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    auto data = std::pair(*i, false);
    RBT::addnode(data, this->root, false);
  }
}
template <class Key, class T>
set<Key, T> &set<Key, T>::operator=(set &&s) noexcept {
  this->root = s.root;
  s.root = nullptr;
  return *this;
}
template <class Key, class T>
void set<Key, T>::clear() noexcept {
  RBT::destroy(this->root);
  this->root = nullptr;
}
template <class Key, class T>
typename set<Key, T>::insert_result set<Key, T>::insert(
    const value_type &value) {
  auto data = std::pair(value, false);
  return RBT::addnode(data, this->root, false);
}

template <class Key, class T>
void set<Key, T>::erase(iterator pos) {
  typename RBT::tnode *data = RBT::get_current(pos);
  RBT::eraseNode(data);
  --this->tree_size;
}

template <class Key, class T>
void set<Key, T>::merge(set &other) {
  for (auto &it : other) {
    RBT::addnode(it, this->root, false);
  }
}
template <class Key, class T>
typename set<Key, T>::iterator set<Key, T>::find(const Key &key) {
  key_type add_item{};
  iterator item = new typename RBT::tnode(std::pair(add_item, false));
  for (auto i = this->begin(); i != this->end(); ++i) {
    auto cur = RBT::get_current(i);
    if (cur->data.first == key) {
      item.clean_iterator();
      return i;
    }
  }
  item.clean_iterator();
  return item;
}
template <class K, class T>
template <class... Args>
std::vector<std::pair<typename set<K, T>::iterator, bool>> set<K, T>::emplace(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  result.push_back(insert(std::forward<Args>(args)...));
  return result;
}
template <class Key, class T>
void set<Key, T>::swap(set &other) {
  std::swap(this->root, other.root);
  auto temp_size = this->tree_size;
  this->tree_size = other.tree_size;
  other.tree_size = temp_size;
}

}  // namespace s21

#endif  // S21_SET_H
