#include <gtest/gtest.h>

#include "../libraries/s21_multiset.h"

using namespace std;

class TestMultiset : public ::testing::Test {
 public:
  s21::multiset<int> s21_mset_int_1{10, 10, 7,  9, 11, 12, 6, 6,
                                    14, 11, 11, 3, 10, 4,  7, 4};
  std::multiset<int> std_mset_int_1{10, 10, 7,  9, 11, 12, 6, 6,
                                    14, 11, 11, 3, 10, 4,  7, 4};

  s21::multiset<int> s21_mset_int_2{111, 222, 222, 333};
  std::multiset<int> std_mset_int_2{111, 222, 222, 333};

  s21::multiset<std::string> s21_mset_str_3{"Ignis", "Terra", "Aer", "Aqua"};
  std::multiset<std::string> std_mset_str_3{"Ignis", "Terra", "Aer", "Aqua"};
};

TEST_F(TestMultiset, msetCopyConstructor) {
  s21::multiset<int> test_int(s21_mset_int_1);
  auto it_test = s21_mset_int_1.begin();
  auto it_stl = std_mset_int_1.begin();
  for (const auto &i : test_int) {
    EXPECT_EQ(i.first, it_test->first);
    EXPECT_EQ(i.first, *it_stl);
    *it_test++;
    it_stl++;
  }
}
TEST_F(TestMultiset, msetMoveConstructor) {
  s21::multiset<int> test_int(move(s21_mset_int_1));
  multiset<int> stl_test(move(std_mset_int_1));
  auto it = stl_test.begin();
  for (const auto &i : test_int) {
    EXPECT_EQ(i.first, *it);
    *it++;
  }
}
TEST_F(TestMultiset, MsetInitConstructor) {
  s21::multiset<int> s21_test{10, 7, 9, 12, 6, 14, 11, 3, 4};
  auto it = s21_test.begin();
  multiset<int> std_test{10, 7, 9, 12, 6, 14, 11, 3, 4};
  for (const auto &i : std_test) {
    EXPECT_EQ(i, it->first);
    ++it;
  }
}
TEST_F(TestMultiset, MsetSmoozOperator) {
  s21::multiset<string> test_copy1(move(s21_mset_str_3));
  multiset<string> std_test(move(std_mset_str_3));
  EXPECT_EQ(test_copy1.begin()->first, *std_test.begin());
  s21::multiset<int> test_copy2(move(s21_mset_int_2));
  multiset<int> std_test2(move(std_mset_int_2));
  auto it = std_test2.begin();
  for (const auto &i : test_copy2) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestMultiset, MsetBegin) {
  auto test = s21_mset_str_3.begin();
  auto stl = std_mset_str_3.begin();
  auto test_2 = s21_mset_int_1.begin();
  auto stl_2 = std_mset_int_1.begin();
  EXPECT_EQ(test->first, *stl);
  EXPECT_EQ(test_2->first, *stl_2);
}
TEST_F(TestMultiset, MsetEmpty) {
  s21::multiset<int> test_empty;
  EXPECT_TRUE(test_empty.empty());
  EXPECT_FALSE(s21_mset_str_3.empty());
}
TEST_F(TestMultiset, MsetSize) {
  s21::multiset<int> test_empty;
  EXPECT_EQ(test_empty.size(), 0);
  EXPECT_EQ(s21_mset_int_1.size(), std_mset_int_1.size());
}

TEST_F(TestMultiset, maxSizeMethod) {
  EXPECT_EQ(s21_mset_int_1.max_size(), s21_mset_int_2.max_size());
  EXPECT_EQ(std_mset_int_1.max_size(), std_mset_int_2.max_size());
}
TEST_F(TestMultiset, clearMethod) {
  s21_mset_int_2.clear();
  std_mset_int_2.clear();
  s21_mset_str_3.clear();
  std_mset_str_3.clear();
  EXPECT_EQ(s21_mset_int_2.size(), std_mset_int_2.size());
  EXPECT_EQ(s21_mset_str_3.size(), std_mset_str_3.size());
}
TEST_F(TestMultiset, insertMethod) {
  s21_mset_str_3.insert("Aboba");
  std_mset_str_3.insert("Aboba");
  EXPECT_EQ(s21_mset_int_2.count(222), 2);
  s21_mset_int_2.insert(222);
  std_mset_int_2.insert(222);
  EXPECT_EQ(s21_mset_int_2.count(222), std_mset_int_2.count(222));
  EXPECT_EQ(s21_mset_int_2.count(222), 3);
  auto it = std_mset_str_3.begin();
  for (auto &i : s21_mset_str_3) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestMultiset, eraseMethod) {
  auto test_pos = s21_mset_int_1.begin();
  auto std_pos = std_mset_int_1.begin();
  ++test_pos;
  ++test_pos;
  ++std_pos;
  ++std_pos;
  ++test_pos;
  ++std_pos;
  ++test_pos;
  ++std_pos;
  ++test_pos;
  ++std_pos;
  ++test_pos;
  ++std_pos;
  s21_mset_int_1.erase(test_pos);
  std_mset_int_1.erase(std_pos);
  EXPECT_EQ(s21_mset_int_1.size(), std_mset_int_1.size());
  auto s21_test = s21_mset_int_1.begin();
  for (auto &i : std_mset_int_1) {
    EXPECT_EQ(i, s21_test->first);
    ++s21_test;
  }
}
TEST_F(TestMultiset, swapMethod) {
  s21_mset_int_1.swap(s21_mset_int_2);
  std_mset_int_1.swap(std_mset_int_2);
  EXPECT_EQ(s21_mset_int_1.size(), std_mset_int_1.size());
  auto it = std_mset_int_1.begin();
  for (auto &i : s21_mset_int_1) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestMultiset, mergeMethd) {
  s21_mset_int_1.merge(s21_mset_int_2);
  std_mset_int_1.merge(std_mset_int_2);
  EXPECT_EQ(s21_mset_int_1.size(), std_mset_int_1.size());
  auto it = std_mset_int_1.begin();
  for (auto &i : s21_mset_int_1) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
// TEST_F(TestMultiset, findMethod) {
//   EXPECT_EQ(s21_mset_int_2.find(11)->first, 0);
//   EXPECT_EQ(s21_mset_str_3.find("Terra")->first,
//   *std_mset_str_3.find("Terra")); EXPECT_EQ(s21_mset_int_2.find(333)->first,
//   *std_mset_int_2.find(333));
// }
TEST_F(TestMultiset, containsMethod) {
  EXPECT_TRUE(s21_mset_str_3.contains("Ignis"));
  EXPECT_TRUE(s21_mset_str_3.contains("Terra"));
  EXPECT_FALSE(s21_mset_str_3.contains("Reference"));
}
TEST_F(TestMultiset, countMethod) {
  EXPECT_EQ(s21_mset_int_1.count(11), 3);
  EXPECT_EQ(std_mset_int_1.count(11), 3);
  EXPECT_EQ(s21_mset_int_1.count(9), std_mset_int_1.count(9));
  EXPECT_EQ(s21_mset_str_3.count("Aqua"), std_mset_str_3.count("Aqua"));
}
TEST_F(TestMultiset, equal_rangeMethod) {
  EXPECT_EQ(s21_mset_int_2.equal_range(222).first->first,
            *std_mset_int_2.equal_range(222).first);
  EXPECT_EQ(s21_mset_int_2.equal_range(222).second->first,
            *std_mset_int_2.equal_range(222).second);
  auto test_s21 = s21_mset_int_1.equal_range(6);
  auto std_test = std_mset_int_1.equal_range(6);
  EXPECT_EQ(test_s21.first->first, *std_test.first);
  EXPECT_EQ(test_s21.second->first, *std_test.second);
}
TEST_F(TestMultiset, lower_bMethod) {
  auto test_s21 = s21_mset_int_1.lower_bound(14);
  auto test_stl = std_mset_int_1.lower_bound(14);
  auto test_s21_1 = s21_mset_int_1.lower_bound(5);
  auto test_stl_1 = std_mset_int_1.lower_bound(5);
  auto test_s21_2 = s21_mset_int_1.lower_bound(3);
  auto test_stl_2 = std_mset_int_1.lower_bound(3);
  auto test_s21_3 = s21_mset_int_1.lower_bound(1);
  auto test_stl_3 = std_mset_int_1.lower_bound(1);
  EXPECT_EQ(test_s21->first, *test_stl);
  EXPECT_EQ(test_s21_1->first, *test_stl_1);
  EXPECT_EQ(test_s21_2->first, *test_stl_2);
  EXPECT_EQ(test_s21_3->first, *test_stl_3);
}
TEST_F(TestMultiset, upper_bMethod) {
  auto test_s21 = s21_mset_int_1.upper_bound(14);
  auto test_s21_1 = s21_mset_int_1.upper_bound(5);
  auto test_stl_1 = std_mset_int_1.upper_bound(5);
  auto test_s21_2 = s21_mset_int_1.upper_bound(13);
  auto test_stl_2 = std_mset_int_1.upper_bound(13);
  auto test_s21_3 = s21_mset_int_1.upper_bound(1);
  auto test_stl_3 = std_mset_int_1.upper_bound(1);
  // EXPECT_EQ(test_s21->first, 0);
  EXPECT_EQ(test_s21_1->first, *test_stl_1);
  EXPECT_EQ(test_s21_2->first, *test_stl_2);
  EXPECT_EQ(test_s21_3->first, *test_stl_3);
}
TEST_F(TestMultiset, emplaceMethod) {
  auto test_s21_1 = s21_mset_str_3.emplace("Genom");
  auto test_s21_2 = s21_mset_str_3.emplace("Vault");
  auto test_s21_3 = s21_mset_str_3.emplace("Univers");
  auto test_s21_4 = s21_mset_str_3.emplace("Progress");
  EXPECT_EQ(s21_mset_str_3.find("Genom")->first, "Genom");
  EXPECT_EQ(s21_mset_str_3.find("Vault")->first, "Vault");
  EXPECT_EQ(s21_mset_str_3.find("Univers")->first, "Univers");
  EXPECT_EQ(s21_mset_str_3.find("Progress")->first, "Progress");
}