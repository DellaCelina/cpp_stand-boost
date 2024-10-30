#include "test.h"

#include <iostream>
#include <format>


Tester& Tester::instance() {
  static Tester v;
  return v;
}

void Tester::regist(const std::string& name, Func f) {
  funcs_[name] = f;
}

void msg(std::string_view s) {
  std::cout << "::[Tester] " << s << std::endl;
}

void Tester::run(const std::vector<std::string>& args) {
  if (args.empty()) {
    for (auto&& [name, f] : funcs_) run_func(name, f);
  } else {
    for (auto& arg : args) {
      if (auto it = funcs_.find(arg); it != funcs_.end()) {
        auto&& [name, f] = *it;
        run_func(name, f);
      } else {
        msg(std::format("Can't find {}", arg));
      }
    }
  }

  
}

int Tester::run_func(const std::string& name, Func f) {
  msg(std::format("Start test {}", name));
  auto ret = f();
  if (ret == 0) msg("Success test");
  else msg("Fail test");
  msg(std::format("End test {}", name));
  return ret;
}