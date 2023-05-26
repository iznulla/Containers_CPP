#include <gtest/gtest.h>

#include "../libraries/s21_set.h"

using namespace std;

class TestSet : public ::testing::Test {
 public:
  s21::set<int> s21_set_int_1{10, 7,  9, 11, 12, 6, 6, 14,
                              11, 11, 3, 9,  10, 4, 4};
  std::set<int> std_set_int_1{10, 7,  9, 11, 12, 6, 6, 14,
                              11, 11, 3, 9,  10, 4, 4};

  s21::set<int> s21_set_int_2{111, 222, 222, 333};
  std::set<int> std_set_int_2{111, 222, 222, 333};

  s21::set<std::string> s21_set_str_3{"Ignis", "Terra", "Aer", "Aqua"};
  std::set<std::string> std_set_str_3{"Ignis", "Terra", "Aer", "Aqua"};
};

TEST_F(TestSet, setCopyConstructor) {
  s21::set<int> test_int(s21_set_int_1);
  auto it_test = s21_set_int_1.begin();
  auto it_stl = std_set_int_1.begin();
  for (const auto &i : test_int) {
    EXPECT_EQ(i.first, it_test->first);
    EXPECT_EQ(i.first, *it_stl);
    *it_test++;
    it_stl++;
  }
}
TEST_F(TestSet, setMoveConstructor) {
  s21::set<int> test_int(move(s21_set_int_1));
  set<int> stl_test(move(std_set_int_1));
  auto it = stl_test.begin();
  for (const auto &i : test_int) {
    EXPECT_EQ(i.first, *it);
    *it++;
  }
}
TEST_F(TestSet, setInitConstructor) {
  s21::set<int> s21_test{10, 7, 9, 12, 6, 14, 11, 3, 4};
  auto it = s21_test.begin();
  set<int> std_test{10, 7, 9, 12, 6, 14, 11, 3, 4};
  for (const auto &i : std_test) {
    EXPECT_EQ(i, it->first);
    ++it;
  }
}
TEST_F(TestSet, setSmoozOperator) {
  s21::set<string> test_copy1(move(s21_set_str_3));
  set<string> std_test(move(std_set_str_3));
  EXPECT_EQ(test_copy1.begin()->first, *std_test.begin());
  s21::set<int> test_copy2(move(s21_set_int_2));
  set<int> std_test2(move(std_set_int_2));
  auto it = std_test2.begin();
  for (const auto &i : test_copy2) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestSet, setBegin) {
  auto test = s21_set_str_3.begin();
  auto stl = std_set_str_3.begin();
  auto test_2 = s21_set_int_1.begin();
  auto stl_2 = std_set_int_1.begin();
  EXPECT_EQ(test->first, *stl);
  EXPECT_EQ(test_2->first, *stl_2);
}
TEST_F(TestSet, setEmpty) {
  s21::set<int> test_empty;
  EXPECT_TRUE(test_empty.empty());
  EXPECT_FALSE(s21_set_str_3.empty());
}
TEST_F(TestSet, setSize) {
  s21::set<int> test_empty;
  EXPECT_EQ(test_empty.size(), 0);
  EXPECT_EQ(s21_set_int_1.size(), std_set_int_1.size());
}

TEST_F(TestSet, maxSizeMethod) {
  EXPECT_EQ(s21_set_int_1.max_size(), s21_set_int_1.max_size());
  EXPECT_EQ(std_set_int_2.max_size(), std_set_int_2.max_size());
}
TEST_F(TestSet, clearMethod) {
  s21_set_int_2.clear();
  std_set_int_2.clear();
  s21_set_str_3.clear();
  std_set_str_3.clear();
  EXPECT_EQ(s21_set_int_2.size(), std_set_int_2.size());
  EXPECT_EQ(s21_set_str_3.size(), std_set_str_3.size());
}
TEST_F(TestSet, insertMethod) {
  s21_set_str_3.insert("Aboba");
  std_set_str_3.insert("Aboba");
  s21_set_int_2.insert(222);
  std_set_int_2.insert(222);
  auto it = std_set_str_3.begin();
  for (auto &i : s21_set_str_3) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestSet, eraseMethod) {
  auto test_pos = s21_set_int_1.begin();
  auto std_pos = std_set_int_1.begin();
  ++test_pos;
  ++test_pos;
  ++std_pos;
  ++std_pos;
  s21_set_int_1.erase(test_pos);
  std_set_int_1.erase(std_pos);
  EXPECT_EQ(s21_set_int_1.size(), std_set_int_1.size());
  auto s21_test = s21_set_int_1.begin();
  for (auto &i : std_set_int_1) {
    EXPECT_EQ(i, s21_test->first);
    ++s21_test;
  }
}
TEST_F(TestSet, swapMethod) {
  s21_set_int_1.swap(s21_set_int_2);
  std_set_int_1.swap(std_set_int_2);
  EXPECT_EQ(s21_set_int_1.size(), std_set_int_1.size());
  auto it = std_set_int_1.begin();
  for (auto &i : s21_set_int_1) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestSet, mergeMethd) {
  s21_set_int_1.merge(s21_set_int_2);
  std_set_int_1.merge(std_set_int_2);
  EXPECT_EQ(s21_set_int_1.size(), std_set_int_1.size());
  auto it = std_set_int_1.begin();
  for (auto &i : s21_set_int_1) {
    EXPECT_EQ(i.first, *it);
    ++it;
  }
}
TEST_F(TestSet, findMethod) {
  // EXPECT_EQ(s21_set_int_2.find(11)->first, 0);
  EXPECT_EQ(s21_set_str_3.find("Terra")->first, *std_set_str_3.find("Terra"));
  EXPECT_EQ(s21_set_int_2.find(333)->first, *std_set_int_2.find(333));
}
TEST_F(TestSet, containsMethod) {
  EXPECT_TRUE(s21_set_str_3.contains("Ignis"));
  EXPECT_FALSE(s21_set_str_3.contains("Reference"));
}

TEST_F(TestSet, emplaceMethod) {
  auto test_s21_1 = s21_set_str_3.emplace("Genom");
  auto test_s21_2 = s21_set_str_3.emplace("Vault");
  auto test_s21_3 = s21_set_str_3.emplace("Univers");
  auto test_s21_4 = s21_set_str_3.emplace("Progress");
  EXPECT_EQ(s21_set_str_3.find("Genom")->first, "Genom");
  EXPECT_EQ(s21_set_str_3.find("Vault")->first, "Vault");
  EXPECT_EQ(s21_set_str_3.find("Univers")->first, "Univers");
  EXPECT_EQ(s21_set_str_3.find("Progress")->first, "Progress");
}
