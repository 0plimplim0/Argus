#include "utils.hh"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace up = utils::parser;

// Namespace Parser
// TODO: Change to external lib for argument parsing

void up::Test(const utils::parser::Arguments& args){
  for (const auto& filename : args.filenames) {
    std::cout << "Filename: " << filename << "\n";
  }
  for (const auto& flag : args.flags) {
    std::cout << "Flag: " << flag.first << "\n";
    if (flag.second) {
      std::cout << "Value: " << *flag.second << "\n";
    }
  }
}

auto up::getFlag(std::string_view arg){
  return std::find_if(up::flags.begin(), up::flags.end(), [&arg](const auto& p) {
    return p.first == arg;
  });
}

up::Arguments up::ParseArguments(std::vector<std::string_view> args){
  up::Arguments Args;
  for (int i = 0; i <args.size(); i++) {
    if (args[i][0] == '-') {
      auto flag = up::getFlag(args[i]);
      if (flag == up::flags.end()) { Args.success = false; break; }
      if (flag->second) {
        // Require arguments
        if (i < args.size() - 1) { Args.success = false; break;}
        Args.flags.push_back({args[i], args[i+1]});
        i++;
      } else {
        // Don't require arguments
        Args.flags.push_back({args[i], std::nullopt});
      }
    } else {
      Args.filenames.push_back(args[i]);
    }
  }
  return Args;
}