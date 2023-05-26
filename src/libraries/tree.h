#ifndef S21_TREE_H
#define S21_TREE_H
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace s21 {

template <class K, class T = int, class Compare = std::less<K>>
struct TNode {
  using value_type = std::pair<const K, T>;
  using const_reference = const value_type &;

  value_type data;
  TNode *left;
  TNode *right;
  TNode *parent;

  explicit TNode(const_reference value)
      : data(value), left(nullptr), right(nullptr), parent(nullptr){};
  explicit TNode(TNode *x)
      : data(x->data), left(x->left), right(x->right), parent(x->parent){};
};

template <class K, class T, class Compare = std::less<K>>
class Tree {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tnode = TNode<K, T>;
  using size_type = size_t;

 public:
  class mapIterator {
   public:
    mapIterator() = default;
    mapIterator(tnode *node) : current(node) {}
    ~mapIterator() = default;

    mapIterator &operator++();  // переход к следующему элементу
    const mapIterator operator++(int);
    mapIterator &operator--();  // переход к предыдущему элементу
    const mapIterator operator--(int);

    value_type *operator->() const { return &this->current->data; }
    reference operator*() const { return current->data; }

    bool operator==(const mapIterator &a) const noexcept {
      return a.current == current;
    }
    bool operator!=(const mapIterator &a) const noexcept {
      return a.current != current;
    }

    void clean_iterator() {
      if (current == nullptr)
        return;
      else
        delete current;
    }

   protected:
    tnode *current{};

    friend class Tree;
  };

  class constMapIterator : public mapIterator {
   public:
    constMapIterator() : mapIterator(){};
    explicit constMapIterator(const tnode *node) : mapIterator(node) {}
    ~constMapIterator() = default;

    friend mapIterator;
  };

 public:
  using iterator = mapIterator;
  using insert_result = std::pair<iterator, bool>;
  using const_iterator = constMapIterator;

 public:
  Tree() = default;
  Tree(const Tree &m) : Tree() {
    root = fullcopy(m.root), tree_size = m.tree_size;
  }
  Tree(Tree &&m) noexcept : Tree() {
    root = m.root;
    tree_size = m.tree_size;
    m.root = nullptr;
  }
  ~Tree() { destroy(root); }

  iterator begin() noexcept;
  //  [[nodiscard]] const_iterator begin() const noexcept {
  //  const_iterator(begin()); }

  iterator end() { return nullptr; }
  //  [[nodiscard]] const_iterator end() const { return const_iterator(nullptr);
  //  }

  tnode *get_current(iterator pos) { return pos.current; }

 protected:
  insert_result addnode(value_type x, tnode *&tree, bool assign);
  iterator addnodeit(value_type x, tnode *&tree);
  tnode *fullcopy(tnode *tree);
  void destroy(tnode *tree);
  void eraseNode(tnode *&node);
  tnode *findMaxNode(tnode *node);
  tnode *find_data_at(const key_type &key, tnode *node);

  bool containsNode(const key_type &key, tnode *node);

 protected:
  //  Compare comp;
  Compare compare_{};
  tnode *root{};
  size_type tree_size{};

  friend class mapIterator;
};
template <class K, class T, class Compare>
typename Tree<K, T, Compare>::iterator Tree<K, T, Compare>::begin() noexcept {
  tnode *node = root;
  if (!root) {
    mapped_type fake_value{};
    key_type fake_key{};
    auto *fake_node = new tnode(std::pair(fake_key, fake_value));
    node = fake_node;
    delete fake_node;
  }
  while (node->left) {
    node = node->left;
  }
  return iterator(node);
}
template <class K, class T, class Compare>
typename Tree<K, T, Compare>::insert_result Tree<K, T, Compare>::addnode(
    Tree::value_type x, Tree::tnode *&tree, bool assign) {
  insert_result result(tree, false);
  if (tree == nullptr) {
    result.first = tree = new tnode(x);
    result.second = true;
    ++tree_size;
  } else if (compare_(x.first, tree->data.first)) {
    result = addnode(x, tree->left, assign);
    tree->left->parent = tree;
  } else if (compare_(tree->data.first, x.first)) {
    result = addnode(x, tree->right, assign);
    tree->right->parent = tree;
  } else if (assign) {
    tree->data.second = x.second;
    //    result.second = true;
    ++tree_size;
  }
  return result;
}

template <class K, class T, class Compare>
typename Tree<K, T, Compare>::tnode *Tree<K, T, Compare>::fullcopy(
    Tree::tnode *tree) {
  if (tree == nullptr) return nullptr;
  auto *newNode = new tnode(tree->data);
  newNode->left = fullcopy(tree->left);
  newNode->right = fullcopy(tree->right);
  return newNode;
}

template <class K, class T, class Compare>
void Tree<K, T, Compare>::destroy(Tree::tnode *tree) {
  if (tree == nullptr) return;
  destroy(tree->left);
  destroy(tree->right);
  delete tree;
  --tree_size;
}
template <class K, class T, class Compare>
void Tree<K, T, Compare>::eraseNode(Tree::tnode *&node) {
  if (node == nullptr) return;
  if (!node->left && !node->right) {
    if (node == root) {
      root = nullptr;
    } else if (node == node->parent->left) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }
  } else if (node->left && !node->right) {
    if (node == root) {
      root = node->left;
    } else if (node == node->parent->left) {
      node->parent->left = node->left;
    } else {
      node->parent->right = node->left;
    }
    node->left->parent = node->parent;
  } else if (node->right && !node->left) {
    if (node == root) {
      root = node->right;
    } else if (node == node->parent->right) {
      node->parent->right = node->right;
    } else {
      node->parent->left = node->right;
    }
    node->right->parent = node->parent;
  } else {
    tnode *localMax = findMaxNode(node->left);

    if (localMax != node->left) {
      if (localMax->left) {
        localMax->left->parent = localMax->parent;
        localMax->parent->right = localMax->left;
      }
      localMax->parent->right = nullptr;
      node->left->parent = localMax;
      localMax->left = node->left;
    }
    localMax->parent = node->parent;
    localMax->right = node->right;
    node->right->parent = localMax;
    if (node->parent && node == node->parent->right) {
      node->parent->right = localMax;
    } else if (node->parent && node == node->parent->left) {
      node->parent->left = localMax;
    }
    if (node->parent == nullptr) root = localMax;
  }
  delete node;
}
template <class K, class T, class Compare>
typename Tree<K, T, Compare>::tnode *Tree<K, T, Compare>::findMaxNode(
    Tree::tnode *node) {
  if (!node->right) return node;
  while (node->right) {
    node = node->right;
  }
  return node;
}

template <class K, class T, class Compare>
bool Tree<K, T, Compare>::containsNode(const key_type &key, Tree::tnode *node) {
  if (!node) return false;
  if (!compare_(node->data.first, key) && !compare_(key, node->data.first))
    return true;
  bool status = false;
  if (compare_(key, node->data.first)) status = containsNode(key, node->left);
  if (compare_(node->data.first, key)) status = containsNode(key, node->right);
  return status;
}

template <class K, class T, class Compare>
typename Tree<K, T, Compare>::iterator Tree<K, T, Compare>::addnodeit(
    Tree::value_type x, Tree::tnode *&tree) {
  iterator result(tree);
  if (tree == nullptr) {
    ++tree_size;
    tree = new tnode(x);
    result = tree;
  } else if (compare_(x.first, tree->data.first) ||
             (!compare_(x.first, tree->data.first) &&
              !compare_(tree->data.first, x.first))) {
    result = addnodeit(x, tree->left);
    tree->left->parent = tree;
  } else if (compare_(tree->data.first, x.first)) {
    result = addnodeit(x, tree->right);
    tree->right->parent = tree;
  }
  return result;
}
template <class K, class T, class Compare>
typename Tree<K, T, Compare>::tnode *Tree<K, T, Compare>::find_data_at(
    const key_type &key, Tree::tnode *node) {
  if (node == nullptr) {
    return nullptr;
  } else {
    if (!compare_(node->data.first, key) && !compare_(key, node->data.first))
      return node;
    if (compare_(key, node->data.first))
      return find_data_at(key, node->left);
    else
      return find_data_at(key, node->right);
  }
}

template <class K, class T, class Compare>
typename Tree<K, T, Compare>::mapIterator &
Tree<K, T, Compare>::mapIterator::operator++() {
  if (current->right) {
    current = current->right;
    while (current->left) {
      current = current->left;
    }
  } else {
    tnode *parent = current->parent;
    while (parent && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}
template <class K, class T, class Compare>
const typename Tree<K, T, Compare>::mapIterator
Tree<K, T, Compare>::mapIterator::operator++(int) {
  mapIterator temp = *this;
  ++(*this);
  return temp;
}
template <class K, class T, class Compare>
typename Tree<K, T, Compare>::mapIterator &
Tree<K, T, Compare>::mapIterator::operator--() {
  if (current->left) {
    current = current->left;
    while (current->right) {
      current = current->right;
    }
  } else {
    tnode *parent = current->parent;
    while (parent && current == parent->left) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}
template <class K, class T, class Compare>
const typename Tree<K, T, Compare>::mapIterator
Tree<K, T, Compare>::mapIterator::operator--(int) {
  mapIterator temp = *this;
  --(*this);
  return temp;
}

}  // namespace s21

#endif  //  S21_TREE_H
