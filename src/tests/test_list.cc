#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../libraries/s21_containers.h"

template <class T>
class ContainersTest : public ::testing::Test {};

struct Person {
  std::string name{};
  std::string country{};
  int year;
  Person() = default;
  Person(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {}

  Person(const Person& other)
      : name(other.name), country(other.country), year(other.year) {}

  Person(Person&& other)
      : name(std::move(other.name)),
        country(std::move(other.country)),
        year(other.year) {}

  Person& operator=(const Person& other) = default;
};

using Types = ::testing::Types<int, double, std::string>;

TYPED_TEST_CASE_P(ContainersTest);

TYPED_TEST_P(ContainersTest, List_edit) {
  TypeParam v1, v2, v3, v4, v5;
  TypeParam i1, i2, i3;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
    i1 = "123", i2 = "901", i3 = "77";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
    i1 = 123, i2 = 901, i3 = 77;
  }

  s21::List<TypeParam> lst_{v1, v2, v3, v4, v5};
  std::list<TypeParam> lst{v1, v2, v3, v4, v5};

  lst_.push_front(i1);
  lst_.push_back(i2);
  lst_.push_front(i1);
  lst_.push_back(i2);
  lst_.pop_back();
  lst_.pop_front();

  lst.push_front(i1);
  lst.push_back(i2);
  lst.push_front(i1);
  lst.push_back(i2);
  lst.pop_back();
  lst.pop_front();

  s21::List<Person> prsn;
  std::list<Person> prsn_std;

  prsn.emplace(prsn.begin(), "VOVA", "RUSSIA", 1999);
  prsn_std.emplace(prsn_std.begin(), "VOVA", "RUSSIA", 1999);
  prsn_std.emplace_back("MASHA", "RUSSIA", 1992);
  prsn.emplace_back("MASHA", "RUSSIA", 1992);

  auto it = lst.begin();
  it = lst.insert(it, i3);
  ++it;
  it = lst.insert(it, i3);
  it = lst.end();
  it = lst.insert(it, i3);

  auto itt = lst_.begin();
  itt = lst_.insert(itt, i3);
  ++itt;
  itt = lst_.insert(itt, i3);
  itt = lst_.end();
  itt = lst_.insert(itt, i3);

  ASSERT_EQ(*it, *itt);
  it = lst.begin();

  for (auto& i : lst_) {
    ASSERT_EQ(i, *it);
    ++it;
  }
  ASSERT_EQ(lst_.size(), lst.size());
}

TYPED_TEST_P(ContainersTest, List_empty_1) {
  TypeParam v1;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75";
  } else {
    v1 = 396.75;
  }

  // Erase #1
  s21::List<TypeParam> emp{v1};
  emp.erase(emp.begin());
  // std::
  std::list<TypeParam> emp_std{v1};
  emp_std.erase(emp_std.begin());
  ASSERT_EQ(emp.empty(), emp_std.empty());
}

TYPED_TEST_P(ContainersTest, List_empty_2) {
  TypeParam v1, v2, v3, v4;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887;
  }
  // Erase #2
  s21::List<TypeParam> emp1{v1, v2, v3, v4};
  emp1.erase(emp1.begin());
  // std::
  std::list<TypeParam> emp_std1{v1, v2, v3, v4};
  emp_std1.erase(emp_std1.begin());
  ASSERT_EQ(emp1.empty(), emp_std1.empty());
}

TYPED_TEST_P(ContainersTest, List_empty_3) {
  TypeParam v1, v2, v3, v4;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887;
  }
  // Erase #3
  std::initializer_list lst{v1, v2, v3, v4};
  s21::List<TypeParam> emp2(lst);
  std::list<TypeParam> emp_std2{lst};
  auto it = emp2.begin();
  ++it;
  // LEAKES!!!
  emp2.erase(it);
  // std::
  auto itt = emp_std2.begin();
  ++itt;
  emp_std2.erase(itt);
  ASSERT_EQ(emp2.empty(), emp_std2.empty());
}

TYPED_TEST_P(ContainersTest, List_empty_4) {
  TypeParam v1, v2, v3, v4;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887;
  }
  // Erase #4
  s21::List<TypeParam> emp3{v1, v2, v3, v4};
  auto it = emp3.tail();
  emp3.erase(it);
  // std::
  std::list<TypeParam> emp_std3{v1, v2, v3, v4};
  auto itt = emp_std3.end();
  --itt;
  emp_std3.erase(itt);
  ASSERT_EQ(emp3.empty(), emp_std3.empty());
}

TYPED_TEST_P(ContainersTest, List_clear) {
  TypeParam v1, v2, v3, v4;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887;
  }
  // Clear #1
  s21::List<TypeParam> clr{v1, v2, v3, v4};
  clr.clear();
  // std::
  std::list<TypeParam> clr_std{v1, v2, v3, v4};
  clr_std.clear();
  ASSERT_EQ(clr.empty(), clr_std.empty());
}

TYPED_TEST_P(ContainersTest, List_constructors) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  size_t m_size = 34;

  std::list<TypeParam> lst_std(m_size);
  s21::List<TypeParam> lst(m_size);
  ASSERT_EQ(lst_std.size(), lst.size());
  std::initializer_list<TypeParam> init_lst{v1, v2, v3, v4, v5};

  std::list<TypeParam> lst_std_copy(init_lst);
  s21::List<TypeParam> lst_copy(init_lst);

  s21::List<TypeParam> lst_c(lst_copy);
  std::list<TypeParam> lst_std_c(lst_std_copy);

  auto it = lst_c.cbegin();
  auto itt = lst_std_c.cbegin();
  while (it != lst_c.cend() && itt != lst_std_c.cend()) {
    ASSERT_EQ(*itt, *it);
    ++it;
    ++itt;
  }

  std::list<TypeParam> lst_std_move(std::move(lst_std_copy));
  s21::List<TypeParam> lst_move(std::move(lst_copy));

  auto itm = lst_move.begin();
  for (auto& i : lst_std_move) {
    ASSERT_EQ(i, *itm);
    ++itm;
  }

  ASSERT_TRUE(lst_copy.empty() == lst_std_copy.empty());
}

TYPED_TEST_P(ContainersTest, List_operator) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  std::initializer_list<TypeParam> init_lst{v1, v2, v3, v4, v5};
  s21::List<TypeParam> lst(init_lst);
  s21::List<TypeParam> eq(init_lst);

  s21::List<TypeParam> lst_move;

  lst_move = std::move(lst);

  auto it = lst_move.begin();
  for (auto& i : lst) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

TYPED_TEST_P(ContainersTest, List_iterator) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  s21::List<TypeParam> eq{v1, v2, v3, v4, v5};
  s21::List<TypeParam> no_eq{v1, v2, v3, v4};

  s21::List<TypeParam> lst{v1, v2, v3, v4, v5};
  std::list<TypeParam> lst_std{v1, v2, v3, v4, v5};

  auto it = lst.begin();
  auto it_std = lst_std.begin();

  it++;
  it_std++;
  ASSERT_EQ(*it_std, *it);

  it--;
  it_std--;
  ASSERT_EQ(*it_std, *it);

  ++it;
  ++it_std;
  ASSERT_EQ(*it_std, *it);

  --it;
  --it_std;
  ASSERT_EQ(*it_std, *it);

  ASSERT_TRUE(lst.front() == eq.front());
  ASSERT_TRUE(lst.back() != no_eq.back());
}

TYPED_TEST_P(ContainersTest, List_splice) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  s21::List<TypeParam> lst;
  std::list<TypeParam> lst_std;

  auto itc = lst.cbegin();
  auto itt = lst_std.cbegin();

  s21::List<TypeParam> splc{v1, v2, v3, v4, v5};
  std::list<TypeParam> splc_std{v1, v2, v3, v4, v5};
  lst.splice(itc, splc);
  lst_std.splice(itt, splc_std);

  auto it = lst.begin();

  for (auto& i : lst_std) {
    ASSERT_EQ(i, *it);
    ++itt;
    ++it;
  }
  s21::List<TypeParam> splc1{v1, v2, v3, v4, v5};
  std::list<TypeParam> splc_std1{v1, v2, v3, v4, v5};

  it = lst.begin();
  itc = ++it;
  itt = lst_std.begin();
  ++itt;

  lst.splice(itc, splc1);
  lst_std.splice(itt, splc_std1);

  it = lst.begin();

  for (auto& i : lst_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }

  s21::List<TypeParam> splc2{v1, v2, v3, v4, v5};
  std::list<TypeParam> splc_std2{v1, v2, v3, v4, v5};

  lst.splice(lst.cend(), splc2);
  lst_std.splice(lst_std.cend(), splc_std2);

  it = lst.begin();

  for (auto& i : lst_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }

  s21::List<TypeParam> splc3{v1, v2, v3, v4, v5};
  std::list<TypeParam> splc_std3{v1, v2, v3, v4, v5};

  lst.splice(lst.cbegin(), splc3);
  lst_std.splice(lst_std.cbegin(), splc_std3);

  it = lst.begin();

  for (auto& i : lst_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

TYPED_TEST_P(ContainersTest, List_swap) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  s21::List<TypeParam> lst{v3, v5, v1};
  std::list<TypeParam> lst_std{v3, v5, v1};

  s21::List<TypeParam> swap{v1, v2, v3, v4, v5};
  std::list<TypeParam> swap_std{v1, v2, v3, v4, v5};

  lst.swap(swap);
  lst_std.swap(swap_std);

  auto it = lst.begin();
  for (auto& i : lst_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

TYPED_TEST_P(ContainersTest, List_sort) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  s21::List<TypeParam> sort{v1, v2, v3, v4, v5};
  std::list<TypeParam> sort_std{v1, v2, v3, v4, v5};

  sort.sort();
  sort_std.sort();

  auto it = sort.begin();
  for (auto& i : sort_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }

  s21::List<TypeParam> sort1{v5, v4, v3, v2, v1};
  std::list<TypeParam> sort_std1{v5, v4, v3, v2, v1};

  sort1.sort();
  sort_std1.sort();

  it = sort1.begin();
  for (auto& i : sort_std1) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

TYPED_TEST_P(ContainersTest, List_reverse) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  s21::List<TypeParam> reverse{v1, v2, v3, v4, v5};
  std::list<TypeParam> reverse_std{v1, v2, v3, v4, v5};

  reverse.reverse();
  reverse_std.reverse();

  auto it = reverse.begin();
  for (auto& i : reverse_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

// // LEAKES!
TYPED_TEST_P(ContainersTest, List_unique) {
  TypeParam v1, v2, v3, v4, v5;

  if constexpr (std::is_same<TypeParam, std::string>::value) {
    v1 = "396.75", v2 = "gendalf", v3 = "ARCH", v4 = "and", v5 = "is_geys";
  } else {
    v1 = 396.75, v2 = 135.00213, v3 = 22.6895, v4 = 33.887, v5 = -396.1;
  }

  std::initializer_list<TypeParam> init_lst{v1, v2, v3, v4, v5};

  s21::List<TypeParam> unique(init_lst);
  std::list<TypeParam> uniaue_std(init_lst);

  unique.unique();
  uniaue_std.unique();

  auto it = unique.begin();
  for (auto& i : uniaue_std) {
    ASSERT_EQ(i, *it);
    ++it;
  }
}

// Register the types to be tested
REGISTER_TYPED_TEST_CASE_P(ContainersTest, List_empty_1, List_empty_2,
                           List_empty_3, List_empty_4, List_clear, List_edit,
                           List_unique, List_reverse, List_sort, List_swap,
                           List_splice, List_iterator, List_operator,
                           List_constructors);

// Instantiate the typed test case with the registered types
INSTANTIATE_TYPED_TEST_CASE_P(TypedTests, ContainersTest, Types);

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
