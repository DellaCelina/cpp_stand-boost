#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class Tester {
 public:
  using Func = std::function<int()>;

  static Tester& instance();
  void regist(const std::string& name, Func f);

  void run(const std::vector<std::string>& args);

 private:
  Tester() = default;

  int run_func(const std::string& name, Func f);

  std::unordered_map<std::string, Func> funcs_;
};

#define TEST(__name)                                  \
int __name();                                         \
class __name##_register {                             \
 public:                                              \
  __name##_register() {                               \
    Tester::instance().regist(#__name, __name);       \
  }                                                   \
};                                                    \
static __name##_register __name##_register_v;         \
int __name()

#define EXPECT_TRUE(...)                                                        \
do {                                                                            \
  if (!(__VA_ARGS__)) {                                                         \
    std::cout << #__VA_ARGS__ << " is expected true but false" << std::endl;    \
    return -1;                                                                  \
  }                                                                             \
} while(false);

#define EXPECT_FALSE(...)                                                       \
do {                                                                            \
  if (__VA_ARGS__) {                                                            \
    std::cout << #__VA_ARGS__ << " is expected false but true" << std::endl;    \
    return -1;                                                                  \
  }                                                                             \
} while(false);
