#include "test.h"
#include "util.h"

#include <source_location>

void log(std::string_view msg, std::source_location loc = std::source_location::current()) {
  print("[{};{}:{} {}] {}\n", loc.file_name(), loc.line(), loc.column(), loc.function_name(), msg);
}

TEST(source_location_test) {
  auto cur = std::source_location::current();
  print("{};{}:{} {}\n", cur.file_name(), cur.line(), cur.column(), cur.function_name());
  log("source location test");

  return 0;
}