#include "test.h"

#include <vector>
#include <string>

class String {
 public:
  String(std::string_view s) {
    auto d = s.data();
    while (*d != '\0') {
      data_.push_back(*d);
      d++;
    }
  }

  auto operator<=>(const String& rhs) const {
    auto len = std::max(data_.size(), rhs.data_.size());

    for (int i = 0; i < len; i++) {
      if (data_.size() <= i) return std::strong_ordering::less;
      if (rhs.data_.size() <= i) return std::strong_ordering::greater;
      auto cmp = data_[i] <=> rhs.data_[i];
      if (std::is_neq(cmp)) return cmp;
    }

    return std::strong_ordering::equal;
  }

 private:
  std::vector<char> data_;
};

TEST(test_3way) {
  String a("ab");
  String b("abc");

  EXPECT_TRUE(std::is_eq(a <=> a));
  EXPECT_TRUE(std::is_neq(a <=> b));
  EXPECT_TRUE(std::is_lt(a <=> b));
  EXPECT_TRUE(std::is_gt(b <=> a));
  EXPECT_TRUE(a < b);
  EXPECT_TRUE(a <= b);
  EXPECT_TRUE(b > a);
  EXPECT_TRUE(b >= a);
  EXPECT_FALSE(a > b);
  EXPECT_FALSE(b < a);

  String c("abc");
  String d("bc");

  EXPECT_TRUE(c < d);
  EXPECT_FALSE(c > d);

  return 0;
}