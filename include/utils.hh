#pragma once

#include <vector>
#include <string>
#include <utility>
#include <optional>

namespace utils {

namespace error_handler {

} // namespace error_handler

namespace formatter {

} // namespace formatter

namespace parser {
struct Arguments {
  std::vector<std::string_view> filenames;
  std::vector<std::pair<std::string_view, std::optional<std::string_view>>> flags;
  bool success = true;
  std::string_view error_message;
};
struct vFlag {
  std::string_view flag;
  std::string_view value;
};

inline const std::vector<std::pair<std::string_view, bool>> flags = {
  {"--pattern", true},
  {"--count", false},
  {"--test", false}
};

void Test(const Arguments& args);
Arguments ParseArguments(std::vector<std::string_view> args);
auto getFlag(std::string_view arg);
vFlag getVflag(std::string_view arg);
} // namespace parser

} // namespace utils