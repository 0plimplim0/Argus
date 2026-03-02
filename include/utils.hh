#pragma once

#include <vector>
#include <string>

namespace utils{

namespace error_handler{

} // namespace error_handler

namespace formatter{

} // namespace formatter

namespace parser{
struct Arguments{
  std::vector<std::string> filenames;
  std::vector<std::string> flags;
  bool success = true;
};
inline const std::vector<std::string_view> flags = {"-v", "-s", "-I"};
void Test(const Arguments& args);
Arguments ParseArguments(std::vector<std::string_view> args);
std::string CheckType(std::string_view arg);
bool ValidateArg(std::string_view arg, std::string_view type);
} // namespace parser

} // namespace utils