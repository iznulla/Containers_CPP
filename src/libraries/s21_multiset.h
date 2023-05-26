#ifndef S21_MULTIMAP_H
#define S21_MULTIMAP_H

#include "tree.h"

namespace s21 {

template <class Key, class T = int>
class multiset : public Tree<Key, T> {
 public:
  using RBT = s21::Tree<Key, T>;
  using key_type = Key;
  using value_type = Key;
  using iterator = typename RBT::mapIterator;
  using const_iterator = typename RBT::constMapIterator;
  using pairiterator = std::pair<iterator, iterator>;
  using size_type = size_t;

  multiset() : RBT(){};
  multiset(std::initializer_list<value_type> const &item);
  multiset(const multiset &ms) : RBT(ms){};
  multiset(multiset &&ms) noexcept { *this = std::move(ms); }
  ~multiset() = default;

  multiset &operator=(multiset &&ms) noexcept;

  bool empty() { return this->size() == 0U; }
  size_type size() { return this->tree_size; };
  [[nodiscard]] size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(typename RBT::tnode) /
           2U;
  };

  void clear() noexcept;  // вопрос об обнулении узлов
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  iterator find(const Key &key);
  bool contains(const key_type &key) {
    return RBT::containsNode(key, this->root);
  }

  size_type count(const Key &key);

  pairiterator equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};
template <class Key, class T>
multiset<Key, T>::multiset(const std::initializer_list<value_type> &item) {
  for (auto i = item.begin(); i != item.end(); ++i) {
    auto data = std::pair(*i, false);
    RBT::addnodeit(data, RBT::root);
  }
}
template <class Key, class T>
multiset<Key, T> &multiset<Key, T>::operator=(multiset &&ms) noexcept {
  this->root = ms.root;
  ms.root = nullptr;
  delete ms.root;
  return *this;
}
template <class Key, class T>
typename multiset<Key, T>::iterator multiset<Key, T>::insert(
    const value_type &value) {
  auto data = std::pair(value, false);
  return RBT::addnodeit(data, this->root);
}
template <class Key, class T>
void multiset<Key, T>::erase(multiset::iterator pos) {
  typename RBT::tnode *data = RBT::get_current(pos);
  RBT::eraseNode(data);
  --this->tree_size;
}
template <class Key, class T>
void multiset<Key, T>::merge(multiset &other) {
  for (auto &it : other) {
    RBT::addnodeit(it, this->root);
  }
}
template <class Key, class T>
typename multiset<Key, T>::iterator multiset<Key, T>::find(const Key &key) {
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
template <class Key, class T>
typename multiset<Key, T>::size_type multiset<Key, T>::count(const Key &key) {
  size_type result = 0U;
  for (auto i = this->begin(); i != this->end(); ++i) {
    auto cur = RBT::get_current(i);
    if (cur->data.first == key) result++;
  }
  return result;
}
template <class Key, class T>
typename multiset<Key, T>::iterator multiset<Key, T>::lower_bound(
    const Key &key) {
  iterator item = this->begin();
  for (auto i = this->begin(); i != this->end(); ++i) {
    item = RBT::get_current(i);
    if (item->first == key) {
      return (item);
    } else if (item->first > key)
      return item;
  }
  return item;
}
template <class Key, class T>
typename multiset<Key, T>::iterator multiset<Key, T>::upper_bound(
    const Key &key) {
  key_type nul{};
  iterator item = new typename RBT::tnode(std::pair(nul, false));
  for (auto i = this->begin(); i != this->end(); ++i) {
    if (i->first > key) {
      item.clean_iterator();
      return i;
    }
  }
  item.clean_iterator();
  return item;
}
template <class Key, class T>
typename multiset<Key, T>::pairiterator multiset<Key, T>::equal_range(
    const Key &key) {
  std::pair<iterator, iterator> result(lower_bound(key), upper_bound(key));
  return result;
}
template <class Key, class T>
template <class... Args>
std::vector<std::pair<typename multiset<Key, T>::iterator, bool>>
multiset<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  result.push_back(std::pair(insert(std::forward<Args>(args)...), true));
  return result;
}
template <class Key, class T>
void multiset<Key, T>::swap(multiset &other) {
  std::swap(this->root, other.root);
  auto temp_size = this->tree_size;
  this->tree_size = other.tree_size;
  other.tree_size = temp_size;
}
template <class Key, class T>
void multiset<Key, T>::clear() noexcept {
  RBT::destroy(this->root);
  this->root = nullptr;
}
}  // namespace s21
#endif  //  S21_MULTIMAP_H