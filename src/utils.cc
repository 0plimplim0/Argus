#include "utils.hh"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace up = utils::parser;

// Namespace Parser

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

up::vFlag up::getVflag(std::string_view arg) {
  size_t  pos = arg.find(':');
  if (pos == std::string_view::npos) { return {}; }
  return {
    arg.substr(0, pos),
    arg.substr(pos + 1)
  };
}

up::Arguments up::ParseArguments(std::vector<std::string_view> args){
  up::Arguments Args;
  for (std::string_view arg : args) {
    if (!arg.empty() && arg[0] == '-') {
      auto flag = up::getFlag(arg);
      if (flag == up::flags.end()) {
        Args.success = false;
        Args.error_message = "One of the flags entered does not exist.";
        break;
      }
      if (flag->second) {
        // Require arguments
        auto [Flag, Value] = up::getVflag(arg);
        if (Flag.empty() || Value.empty()) {
          Args.success = false;
          Args.error_message = "One of the flags requires an argument but none was provided.";
          break;
        }
        Args.flags.push_back({Flag, Value});
      } else {
        // Don't require arguments
        Args.flags.push_back({arg, std::nullopt});
      }
    } else {
      Args.filenames.push_back(arg);
    }
  }
  return Args;
}