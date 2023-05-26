#include <gtest/gtest.h>

#include "../libraries/s21_map.h"

using namespace std;

class TestMap : public ::testing::Test {
 public:
  s21::map<int, int> s21_map_int_1{{10, 10}, {7, 7},   {9, 9}, {12, 12}, {6, 6},
                                   {14, 14}, {11, 11}, {3, 3}, {4, 4}};
  std::map<int, int> std_map_int_1{{10, 10}, {7, 7},   {9, 9}, {12, 12}, {6, 6},
                                   {14, 14}, {11, 11}, {3, 3}, {4, 4}};
  s21::map<int, int> s21_map_int_2{{111, 211}, {222, 112}};
  std::map<int, int> std_map_int_2{{111, 211}, {222, 112}};
  s21::map<int, string> s21_map_int_str_1{
      {5, "Aer"}, {2, "Ignis"}, {1, "Terra"}};
  std::map<int, string> std_map_int_str_1{
      {5, "Aer"}, {2, "Ignis"}, {1, "Terra"}};
  s21::map<int, string> s21_map_int_str_2{{4, "Aqua"}};
  std::map<int, string> std_map_int_str_2{{4, "Aqua"}};
  s21::map<string, int> s21_map_str_int_1{
      {"aer", 5}, {"ignis", 2}, {"terra", 1}};
  std::map<string, int> std_map_str_int_1{
      {"aer", 5}, {"ignis", 2}, {"terra", 1}};
  s21::map<string, int> s21_map_str_int_2{{"aqua", 4}};
  std::map<string, int> std_map_str_int_2{{"aqua", 4}};
};
// testing map constructors
TEST_F(TestMap, mapCopyConstructor) {
  s21::map<int, int> test_copy1(s21_map_int_2);
  s21::map<int, string> test_copy2(s21_map_int_str_1);
  EXPECT_EQ(test_copy1.begin()->first, s21_map_int_2.begin()->first);
  EXPECT_EQ(test_copy2.begin()->second, s21_map_int_str_1.begin()->second);
}
TEST_F(TestMap, mapMoveConstruector) {
  s21::map<int, int> test_copy1(s21_map_int_1);
  s21::map<int, int> test_move1(move(s21_map_int_1));
  s21::map<int, string> test_copy2(s21_map_int_str_1);
  s21::map<int, string> test_move2(move(s21_map_int_str_1));
  EXPECT_EQ(test_copy1.begin()->first, test_move1.begin()->first);
  EXPECT_EQ(test_copy2.begin()->second, test_move2.begin()->second);
}
TEST_F(TestMap, mapInitializeConstruector) {
  s21::map<int, int> test_initialize{{10, 10}, {7, 7}, {9, 9},
                                     {12, 12}, {6, 6}, {14, 14},
                                     {11, 11}, {3, 3}, {4, 4}};
  map<int, int> std_test_init{{10, 10}, {7, 7},   {9, 9}, {12, 12}, {6, 6},
                              {14, 14}, {11, 11}, {3, 3}, {4, 4}};
  auto it = std_test_init.begin();
  for (auto &item : test_initialize) {
    EXPECT_EQ(item.first, it->first);
    ++it;
  }
}
TEST_F(TestMap, mapSmootOperator) {
  s21::map<int, int> test_copy1(s21_map_int_1);
  s21::map<int, int> test_move1;
  test_move1 = move(s21_map_int_1);
  s21::map<int, string> test_copy2(s21_map_int_str_1);
  s21::map<int, string> test_move2;
  test_move2 = move(s21_map_int_str_1);
  EXPECT_EQ(test_copy1.begin()->first, test_move1.begin()->first);
  EXPECT_EQ(test_copy2.begin()->second, test_move2.begin()->second);
}
TEST_F(TestMap, mapBeginMethod) {
  s21::map<int, int> zero;
  // auto test_zero = zero.begin();
  // EXPECT_EQ(test_zero->second, 0);
  auto test = s21_map_int_1.begin();
  auto stl = std_map_int_1.begin();
  auto test_2 = s21_map_int_2.begin();
  auto stl_2 = std_map_int_2.begin();
  EXPECT_EQ(test->first, stl->first);
  EXPECT_EQ(test_2->first, stl_2->first);
}

TEST_F(TestMap, emptyMethod) {
  s21::map<int, int> test;
  EXPECT_FALSE(std_map_int_str_2.empty());
  EXPECT_TRUE(test.empty());
}

TEST_F(TestMap, sizeMethod) {
  EXPECT_EQ(s21_map_int_1.size(), std_map_int_1.size());
  s21_map_int_1.insert({121, 212});
  std_map_int_1.insert({121, 212});
  EXPECT_EQ(s21_map_int_1.size(), std_map_int_1.size());
  s21_map_int_1.erase(s21_map_int_1.begin());
  std_map_int_1.erase(std_map_int_1.begin());
  EXPECT_EQ(s21_map_int_1.size(), std_map_int_1.size());
}

TEST_F(TestMap, maxSizeMethod) {
  EXPECT_EQ(s21_map_int_1.max_size(), s21_map_int_2.max_size());
  EXPECT_EQ(std_map_int_1.max_size(), std_map_int_2.max_size());
}

TEST_F(TestMap, atMethod) {
  auto test_1 = s21_map_int_str_1.at(1);
  auto stl_1 = std_map_int_str_1.at(1);
  EXPECT_EQ(test_1, stl_1);
  // EXPECT_ANY_THROW(s21_map_int_2.at(2213));
  // EXPECT_ANY_THROW(std_map_int_2.at(2213));
}
TEST_F(TestMap, operatorAtMethod) {
  EXPECT_EQ(s21_map_int_str_1[1], std_map_int_str_1[1]);
  EXPECT_EQ(s21_map_int_str_1[555], std_map_int_str_1[555]);
  EXPECT_EQ(s21_map_int_str_1.size(), std_map_int_str_1.size());
  s21_map_int_str_1[555] = "BIK";
  std_map_int_str_1[555] = "BIK";
  EXPECT_EQ(s21_map_int_str_1[555], std_map_int_str_1[555]);
}

TEST_F(TestMap, clearMethod) {
  s21_map_str_int_1.clear();
  std_map_str_int_1.clear();
  s21_map_int_str_2.clear();
  std_map_int_str_2.clear();
  EXPECT_EQ(s21_map_str_int_1.size(), std_map_str_int_1.size());
  EXPECT_EQ(s21_map_int_str_2.size(), std_map_int_str_2.size());
}
TEST_F(TestMap, insertPairMethod) {
  auto add_item = pair<int, int>(311, 113);
  auto add_has_item = pair<int, int>(10, 10);
  auto test_return_true = s21_map_int_2.insert(add_item);
  auto stl_return_true = std_map_int_2.insert(add_item);
  auto test_return_false = s21_map_int_2.insert(add_has_item);
  auto stl_return_false = std_map_int_2.insert(add_has_item);
  auto it = s21_map_int_2.begin();

  // testing correct data
  for (const auto &i : std_map_int_2) {
    EXPECT_EQ(i.first, it->first);
    ++it;
  }
  // testing bool returned
  EXPECT_EQ(test_return_true.second, stl_return_true.second);
  EXPECT_EQ(test_return_false.second, stl_return_false.second);
}
TEST_F(TestMap, insertMethod) {
  auto test_return_true = s21_map_int_2.insert({311, 113});
  auto stl_return_true = std_map_int_2.insert({311, 113});
  auto test_return_false = s21_map_int_2.insert({10, 10});
  auto stl_return_false = std_map_int_2.insert({10, 10});
  auto it = s21_map_int_2.begin();

  // testing correct data
  for (const auto &i : std_map_int_2) {
    EXPECT_EQ(i.first, it->first);
    ++it;
  }
  // testing bool returned
  EXPECT_EQ(test_return_true.second, stl_return_true.second);
  EXPECT_EQ(test_return_false.second, stl_return_false.second);
}
TEST_F(TestMap, insert_or_assignMethod) {
  auto test_return_false = s21_map_int_2.insert_or_assign(311, 113);
  auto stl_return_false = std_map_int_2.insert_or_assign(311, 113);
  auto test_return_true = s21_map_int_2.insert_or_assign(111, 1);
  auto stl_return_true = std_map_int_2.insert_or_assign(111, 1);
  auto it = s21_map_int_2.begin();

  // testing correct data
  for (const auto &i : std_map_int_2) {
    EXPECT_EQ(i.first, it->first);
    ++it;
  }
  // testing bool returned
  EXPECT_EQ(test_return_false.second, stl_return_false.second);
  EXPECT_EQ(test_return_true.second, stl_return_true.second);
}

TEST_F(TestMap, eraseMethod) {
  auto test_1 = s21_map_int_str_1.begin();
  auto stl_1 = std_map_int_str_1.begin();
  test_1++;
  stl_1++;
  test_1++;
  stl_1++;
  s21_map_int_str_1.erase(test_1);
  std_map_int_str_1.erase(stl_1);
  EXPECT_EQ(s21_map_int_str_1.size(), std_map_int_str_1.size());
  auto it = std_map_int_str_1.begin();
  for (auto &i : s21_map_int_str_1) {
    EXPECT_EQ(i.first, it->first);
    it++;
  }
}
TEST_F(TestMap, swapMethod) {
  s21_map_int_1.swap(s21_map_int_2);
  std_map_int_1.swap(std_map_int_2);
  auto it = std_map_int_1.begin();
  for (auto &i : s21_map_int_1) {
    EXPECT_EQ(i.first, it->first);
    it++;
  }
}
TEST_F(TestMap, mergeMethod) {
  s21_map_int_1.merge(s21_map_int_2);
  std_map_int_1.merge(std_map_int_2);
  auto it = std_map_int_1.begin();
  for (auto &i : s21_map_int_1) {
    EXPECT_EQ(i.first, it->first);
    it++;
  }
}
TEST_F(TestMap, containsMethod) {
  EXPECT_TRUE(s21_map_int_1.contains(10));
  EXPECT_FALSE(s21_map_int_2.contains(10));
}
TEST_F(TestMap, emplaceMethod) {
  s21_map_str_int_1.emplace("Genom", 120);
  std_map_str_int_1.emplace("Genom", 120);
  auto it = std_map_str_int_1.begin();
  for (auto &i : s21_map_str_int_1) {
    EXPECT_EQ(i.first, it->first);
    it++;
  }
}
