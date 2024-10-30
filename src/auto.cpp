#include "test.h"

#include <type_traits>

TEST(keyword_auto) {
  auto a = 5;
  EXPECT_TRUE(std::is_same_v<decltype(a), int>);

  const auto b = a;
  EXPECT_TRUE(std::is_same_v<decltype(b), const int>);

  // Error
  // const auto* c = b;

  const auto* d = &b;
  EXPECT_TRUE(std::is_same_v<decltype(d), const int*>);

  // const is not decayed if using auto with reference
  auto& e = b;
  EXPECT_TRUE(std::is_same_v<decltype(e), const int&>);

  // const & reference is decayed if using auto
  auto f = e;
  EXPECT_TRUE(std::is_same_v<decltype(f), int>);

  // const & reference is not decayed if using decltype(auto)
  decltype(auto) g = e;
  EXPECT_TRUE(std::is_same_v<decltype(g), const int&>);

  // const is not decayed if target is pointer
  auto h = d;
  EXPECT_TRUE(std::is_same_v<decltype(h), const int*>);

  // const is not decayed if using auto with forwarding
  auto&& i = e;
  EXPECT_TRUE(std::is_same_v<decltype(i), const int&>);

  struct AutoTest {
    auto auto_test() { return v; }
    auto& auto_ref_test() { return v; }
    auto& auto_const_ref_test() const { return v; }
    int v;
  };

  auto t = AutoTest();
  EXPECT_TRUE(std::is_same_v<decltype(std::declval<AutoTest>().auto_test()), int>);
  EXPECT_TRUE(std::is_same_v<decltype(std::declval<AutoTest>().auto_ref_test()), int&>);
  EXPECT_TRUE(std::is_same_v<decltype(std::declval<AutoTest>().auto_const_ref_test()), const int&>);

  auto k = {1, 2};
  EXPECT_TRUE(std::is_same_v<decltype(k), std::initializer_list<int>>);

  return 0;
}