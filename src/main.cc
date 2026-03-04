#include "utils.hh"

#include <iostream>
#include <string>
#include <vector>

namespace up = utils::parser;

// 0: No errors | 1: Argument error | 2: File error
int main(int argc, char** argv){
  
  if (argc < 2) {
    std::cerr << "Usage: argus [OPTIONS] <filename>" << std::endl;
    return 1;
  }

  std::vector<std::string_view> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  up::Arguments Args = up::ParseArguments(args);
  if (Args.success) {
    up::Test(Args);
  } else {
    std::cout << Args.error_message << "\n";
    return 1;
  }
  return 0;
}