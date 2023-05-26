#include <initializer_list>
#include <iostream>
#include <limits>

template <class T>
class Vector {
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // constructors
  Vector() : m_size(0U), m_capacity(0U), arr(nullptr){};

  explicit Vector(size_type n)
      : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr){};

  Vector(std::initializer_list<value_type> const &items) {
    arr = new value_type[items.size()];
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
    m_size = items.size();
    m_capacity = items.size();
  };

  // copy constructor with simplified syntax
  Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity) {
    arr = new value_type[m_capacity];
    for (size_type i = 0; i < v.m_size; ++i) {
      arr[i] = v.arr[i];
    }
  };

  // move constructor with simplified syntax
  Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.arr = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  };

  // destructor
  ~Vector() { delete[] arr; }

  Vector &operator=(Vector &&v) {
    m_size = v.m_size;
    m_capacity >= v.m_capacity ? m_capacity : m_capacity = v.m_capacity;
    arr = v.arr;
    v.arr = nullptr;
    v.m_size = v.m_capacity = 0;
    return *this;
  };

  // Vector Element access
  reference at(size_type pos) { return arr[pos]; }  // pos > size

  reference operator[](size_type pos) { return arr[pos]; }

  const_reference front() { return arr[0]; }

  const_reference back() { return arr[m_size - 1]; }

  T *data() { return arr; }

  // Vector Iterators
  iterator begin() noexcept { return arr; }
  iterator end() noexcept { return arr + m_size; }

  // Vector Capacity
  bool empty() { return m_size ? false : true; }
  size_type size() { return m_size; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2U;
  }

  void reserve(size_t size) {
    if (size > m_capacity) {
      value_type *buff = new value_type[size];
      for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
      delete[] arr;
      arr = buff;
      m_capacity = size;
    }
  }
  size_type capacity() { return m_capacity; }

  void shrink_to_fit() {
    if (m_size < m_capacity) {
      value_type *buff = new value_type[m_size];
      for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
      delete[] arr;
      arr = buff;
      m_capacity = m_size;
    }
  }

  // Vector Modifiers
  void clear() {
    arr = nullptr;
    m_size = 0;
  }
  iterator insert(iterator pos, const_reference value) {  // 5 5
    value_type *buff = new value_type[m_size + 1];

    size_t position = pos - begin();

    for (size_t i = 0; i < m_size + 1; ++i) {
      if (i < position) {
        buff[i] = arr[i];
      } else if (i == position) {
        buff[i] = value;
        buff[i + 1] = arr[i];
      } else {
        buff[i + 1] = arr[i];
      }
    }
    reserve(m_size * 2);
    m_size++;
    arr = buff;
    return (arr + position);
  }

  void erase(iterator pos) {
    value_type *buff = new value_type[m_size - 1];

    size_t position = pos - begin();

    for (size_t i = 0; i < m_size + 1; ++i) {
      if (i < position) {
        buff[i] = arr[i];
      } else if (i > position) {
        buff[i - 1] = arr[i];
      }
    }
    m_size--;
    arr = buff;
  }

  void push_back(value_type v) {
    if (m_size == m_capacity) reserve(m_size * 2);
    arr[m_size++] = v;
  }

  void pop_back() { erase(end() - 1); }

  void swap(Vector &other) {
    value_type *buff = other.arr;
    other.arr = arr;
    arr = buff;
    size_type buff_size = other.m_size;
    other.m_size = m_size;
    m_size = buff_size;
    size_type buff_capacity = other.m_capacity;
    other.m_capacity = m_capacity;
    m_capacity = buff_capacity;
  }

 private:
  size_t m_size;
  size_t m_capacity;
  value_type *arr;
};