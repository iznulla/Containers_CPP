#ifndef CPP2_S21_CONTAINERS_LIBRARIES_S21_LIST_H_
#define CPP2_S21_CONTAINERS_LIBRARIES_S21_LIST_H_

namespace s21 {
template <class T>

class List {
 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListNode {
   public:
    value_type value_;
    ListNode *prev_;
    ListNode *next_;
    ListNode() : value_(), prev_(nullptr), next_(nullptr) {}
    ListNode(const value_type value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  class ListIterator {
   public:
    ListIterator() : current_() {}
    ListIterator(ListNode *current) : current_(current) {}
    reference operator*() const { return current_->value_; }
    pointer operator->() const { return &current_->value_; }

    // Pre-increment
    ListIterator &operator++() {
      current_ = current_->next_;
      return *this;
    }

    // Post-increment
    ListIterator operator++(int) {
      ListIterator tmp = *this;
      current_ = current_->next_;
      return tmp;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      current_ = current_->prev_;
      return tmp;
    }

    ListIterator &operator--() {
      current_ = current_->prev_;
      return *this;
    }

    bool operator==(const ListIterator &other) {
      return current_ == other.current_;
    }

    bool operator!=(const ListIterator &other) {
      return current_ != other.current_;
    }

   private:
    ListNode *current_;

    friend class List;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    ListConstIterator(const ListConstIterator &current)
        : ListIterator(current) {}

    ListConstIterator(const ListIterator &current) : ListIterator(current) {}

    ListConstIterator operator=(const ListConstIterator &current) {
      ListIterator::operator=(current);
      return *this;
    }
    const_reference operator*() const { return ListIterator::operator*(); }
  };

 public:
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Constructors and destructor
  List() { initList(); }

  List(size_type n) {
    initList();
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  List(std::initializer_list<value_type> const &items) {
    initList();
    for (const auto &item : items) {
      push_back(item);
    }
  }

  List(const List &l) {
    initList();
    for (auto it = l.cbegin(); it != l.cend(); ++it) {
      push_back(*it);
    }
  }

  List(List &&l) {
    initList();
    for (auto i : l) {
      push_back(i);
    }
    l.clear();
  }

  ~List() {
    while (head_) {
      ListNode *next = head_;
      head_ = head_->next_;
      delete next;
    }
    initList();
  }

  // Operators
  List &operator=(List &&l) {
    initList();
    for (auto &i : l) {
      push_back(i);
    }
    return *this;
  }

  // Additional functions
  void initList() {
    head_ = tail_ = nullptr;
    m_size_ = 0;
  }

  // List Element
  const_reference front() { return head_->value_; }
  const_reference back() { return tail_->value_; }

  iterator tail() { return iterator(tail_); }

  // // List Iterators
  const_iterator cbegin() const { return const_iterator(head_); }

  const_iterator cend() const { return const_iterator(tail_->next_); }

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(tail_->next_); }

  // List Capacity
  bool empty() { return m_size_ == 0 ? true : false; }
  size_type size() { return m_size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type);
  }

  void push_back(const_reference value) {
    std::unique_ptr<ListNode> newTail(new ListNode(value));
    if (tail_) {
      newTail->prev_ = tail_;
      tail_->next_ = newTail.get();
      tail_ = newTail.get();
    } else {
      tail_ = head_ = newTail.get();
    }
    ++m_size_;
    newTail.release();
  }

  void pop_back() {
    if (empty()) {
      throw std::out_of_range("Error: List is empty.");
    } else {
      // ListNode *oldTail = tail_;
      std::unique_ptr<ListNode> oldTail(tail_);
      if (m_size_ < 2) {
        head_ = tail_ = nullptr;
      } else {
        tail_ = tail_->prev_;
        tail_->next_ = nullptr;
      }
      --m_size_;
    }
  }

  void push_front(const_reference value) {
    std::unique_ptr<ListNode> newHead(new ListNode(value));
    // ListNode *newHead = new ListNode(value);
    if (head_) {
      newHead->next_ = head_;
      head_->prev_ = newHead.get();
      head_ = newHead.get();
    } else {
      head_ = tail_ = newHead.get();
    }
    ++m_size_;
    newHead.release();
  }

  void pop_front() {
    if (empty()) {
      throw std::out_of_range("Error: List is empty.");
    } else {
      // ListNode *oldHead = head_;
      std::unique_ptr<ListNode> oldHead(head_);
      if (m_size_ < 2) {
        head_ = tail_ = nullptr;
      } else {
        head_ = head_->next_;
        head_->prev_ = nullptr;
      }
      --m_size_;
    }
  }
  void swap(List &other) {
    std::swap(m_size_, other.m_size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  ListNode *merge_sorted_lists(ListNode *left, ListNode *right) {
    ListNode dummy_head;
    ListNode *current = &dummy_head;

    while (left && right) {
      if (std::less_equal()(left->value_, right->value_)) {
        left->prev_ = current;
        current->next_ = left;
        left = left->next_;
      } else {
        right->prev_ = current;
        current->next_ = right;
        right = right->next_;
      }
      current = current->next_;
    }

    if (left) {
      left->prev_ = current;
      current->next_ = left;
    } else {
      right->prev_ = current;
      current->next_ = right;
    }

    return dummy_head.next_;
  }

  void get_tail_of_list(ListNode *head) {
    ListNode *it = head;
    ListNode *prev;

    while (it) {
      if (!it->next_) prev = it;
      it = it->next_;
    }
    tail_ = prev;
  }

  ListNode *get_middle_listnode(ListNode *head) {
    if (!head || !head->next_) return head;

    ListNode *slow = head;
    ListNode *fast = head->next_;

    while (fast) {
      fast = fast->next_;
      if (fast) {
        slow = slow->next_;
        fast = fast->next_;
      }
    }

    ListNode *middle = slow->next_;

    slow->next_ = nullptr;
    middle->prev_ = nullptr;

    ListNode *left = get_middle_listnode(head);
    ListNode *right = get_middle_listnode(middle);

    return merge_sorted_lists(left, right);
  }

  void merge(List &other) {
    tail_->next_ = other.head_;
    other.head_->prev_ = tail_;
    tail_ = other.tail_;
    m_size_ += other.m_size_;

    other.head_ = nullptr;
    // other.tail_ = nullptr;
    other.m_size_ = 0;
  }

  void append_list(const_iterator pos, List &other) {
    ListNode *current = pos.current_;
    ListNode *prev = current->prev_;

    current->prev_ = other.tail_;
    prev->next_ = other.head_;

    other.tail_->next_ = current;
    other.head_->prev_ = prev;
    m_size_ += other.m_size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.m_size_ = 0;
  }

  // PRINT OTHER SEGMENTATION FAULT
  void splice(const_iterator pos, List &other) {
    if (other.m_size_ < 1) return;
    if (m_size_ < 1) {
      for (auto &i : other) {
        push_back(i);
      }
    } else {
      if (pos == cbegin()) {
        other.tail_->next_ = head_;
        head_->prev_ = other.tail_;
        head_ = other.head_;

        m_size_ += other.m_size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.m_size_ = 0;
      } else if (pos == cend()) {
        merge(other);
      } else {
        append_list(pos, other);
      }
    }
  }

  void reverse() {
    if (m_size_ < 2) return;

    ListNode *current = head_;
    ListNode *next = nullptr;
    ListNode *prev = nullptr;

    while (current) {
      next = current->next_;
      current->prev_ = next;
      current->next_ = prev;
      prev = current;
      current = next;
    }

    std::swap(head_, tail_);
  };

  void unique() {
    ListNode *current = tail_;

    if (m_size_ < 2) return;

    while (current->prev_) {
      if (current->value_ == current->prev_->value_) {
        iterator duplicate = current;
        current = current->prev_;
        erase(duplicate);
        duplicate = nullptr;
      } else {
        current = current->prev_;
      }
    }
  }

  void sort() {
    if (m_size_ < 2) return;

    head_ = get_middle_listnode(head_);
    head_->prev_ = nullptr;
    get_tail_of_list(head_);
  }

  // List Modifiers
  void clear() {
    while (m_size_) {
      pop_back();
    }
  }

  void append_value(iterator pos, const_reference value) {
    ListNode *current = pos.current_;
    ListNode *prev = current->prev_;
    ListNode *newElement = new ListNode(value);

    newElement->next_ = current;
    newElement->prev_ = prev;
    current->prev_ = newElement;
    prev->next_ = newElement;
    ++m_size_;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value);
      pos = head_;
    } else if (pos == end()) {
      push_back(value);
      pos = tail_;
    } else {
      append_value(pos, value);
      --pos;
    }
    return pos;
  }

  void erase(iterator pos) {
    std::unique_ptr<ListNode> current(pos.current_);
    if (current.get() == head_ && current.get() == tail_) {
      head_ = tail_ = nullptr;
    } else if (current.get() == head_) {
      head_ = head_->next_;
      head_->prev_ = nullptr;
    } else if (current.get() == tail_) {
      tail_ = tail_->prev_;
      tail_->next_ = nullptr;
    } else {
      current->prev_->next_ = current->next_;
      current->next_->prev_ = current->prev_;
    }
    --m_size_;
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    value_type newArg(std::forward<Args>(args)...);
    return insert(pos, newArg);
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    value_type newArg(std::forward<Args>(args)...);
    push_back(newArg);
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    value_type newArg(std::forward<Args>(args)...);
    push_front(newArg);
  }

 private:
  size_type m_size_;
  ListNode *head_;
  ListNode *tail_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIBRARIES_S21_LIST_H_