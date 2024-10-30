#include "test.h"

#include <vector>
#include <string>

int main(int argc, char** argv) {
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++)
    args.emplace_back(argv[i]);

  Tester::instance().run(args);
  return 0;
}