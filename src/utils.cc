#include "utils.hh"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// Namespace Parser

void utils::parser::Test(const utils::parser::Arguments& args){
  for (std::string_view filename : args.filenames) {
    std::cout << "filename: " << filename << "\n";
  }
  for (std::string_view flag : args.flags) {
    std::cout << "Flag: " << flag << "\n";
  }
}

utils::parser::Arguments utils::parser::ParseArguments(std::vector<std::string_view> args){
  utils::parser::Arguments Args;
  for (std::string_view arg : args){
    std::string type = utils::parser::CheckType(arg);
    if (utils::parser::ValidateArg(arg, type)){
      std::string Arg{arg};
      if (type == "FILENAME") {
        Args.filenames.push_back(Arg);
      } else {
        Args.flags.push_back(Arg);
      }
    } else {
      Args.success = false;
    }
  }
  return Args;
}

// Returns: FILENAME | FLAG 
// TODO: Use enum class instead std::string
std::string utils::parser::CheckType(std::string_view arg){
  if (arg[0] == '-') {
    return "FLAG";
  } else {
    return "FILENAME";
  }
}

bool utils::parser::ValidateArg(std::string_view arg, std::string_view type){
  // TODO: Remove filename checking, trying open the file already checks
  if (type == "FILENAME") {
    std::error_code ec;
    std::filesystem::file_status f = std::filesystem::status(arg, ec);
    if (ec || ((f.permissions() & std::filesystem::perms::owner_read) == std::filesystem::perms::none)) { return false; }
    else { return true; }
  } else {
    if (std::find(utils::parser::flags.begin(), utils::parser::flags.end(), arg) != utils::parser::flags.end()){
      return true;
    } else { return false; }
  }
}