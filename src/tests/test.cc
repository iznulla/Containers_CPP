#include <gtest/gtest.h>

#include <array>

#include "../libraries/s21_containers.h"
#include "../libraries/s21_containersplus.h"

TEST(StackTest, stack) {
  s21::Stack<int> n = {1, 2, 3, 4};
  s21::Stack<int> k(n);
  EXPECT_EQ(k.empty(), false);
  s21::Stack<int> l(std::move(k));
  s21::Stack<int> q;
  EXPECT_EQ(q.empty(), true);
  q = std::move(l);
  s21::Stack<int> m;
  m.swap(q);
  EXPECT_EQ(m.size(), 4);
  m.push(5);
  m.emplace(6);
  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(m.top(), i);
    m.pop();
  }
}

TEST(QueueTest, queue) {
  s21::Queue<int> n = {1, 2, 3, 4};
  s21::Queue<int> k(n);
  EXPECT_EQ(k.empty(), false);
  s21::Queue<int> l(std::move(k));
  s21::Queue<int> q;
  EXPECT_EQ(q.empty(), true);
  q = std::move(l);
  s21::Queue<int> m;
  m.swap(q);
  m.push(5);
  m.emplace(6);
  EXPECT_EQ(m.size(), 6);
  EXPECT_EQ(m.front(), 1);
  EXPECT_EQ(m.back(), 6);
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(m.front(), i);
    m.pop();
  }
}

TEST(DequeTest, deque) {
  s21::Deque<int> n;
  n.push_front(8);
  EXPECT_EQ(n.front(), 8);
  n.push_front(9);
  EXPECT_EQ(n.front(), 9);
}

TEST(ArrayTest, array) {
  s21::Array<int, 5> n = {1, 2, 3, 4, 5};
  std::array<int, 5> nstd = {1, 2, 3, 4, 5};
  s21::Array<int, 5> m(n);
  s21::Array<int, 5> k(std::move(m));
  s21::Array<int, 0> g;
  std::array<int, 0> gstd;
  s21::Array<int, 5> q = {5, 4, 3, 2, 1};
  s21::Array<int, 5> p = {1, 2, 3, 4, 5};
  s21::Array<int, 5> l;

  EXPECT_EQ(k.empty(), 0);

  EXPECT_EQ(g.empty(), gstd.empty());
  EXPECT_EQ(n.empty(), nstd.empty());
  EXPECT_EQ(n.size(), nstd.size());
  EXPECT_EQ(n.max_size(), nstd.max_size());
  l = std::move(p);
  std::size_t i = 0;
  for (auto it = k.begin(); it != k.end(); ++it) {
    EXPECT_EQ(*it, ++i);
  }
  for (int j = 0; j < 5; j++) {
    EXPECT_EQ(k[j], nstd[j]);
    EXPECT_EQ(k.at(j), nstd.at(j));
    EXPECT_EQ(k.at(j), l[j]);
  }
  k.swap(q);
  EXPECT_EQ(k.front(), 5);
  EXPECT_EQ(k.back(), 1);
  k.fill(6);
  EXPECT_EQ((*k.data()), 6);
  // try {
  //   m.at(67);
  // } catch (std::out_of_range const &err) {
  //   EXPECT_EQ(err.what(), std::string("Incorrect input, no index"));
  // }
}
