#include "utils.hh"
#include "analyzer.hh"
#include "analysis.hh"

#include <iostream>
#include <string>
#include <vector>

namespace up = utils::parser;

// 0: No errors | 1: Parser error | 2: Analyzer error
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
  if (!Args.success) {
    std::cout << Args.error_message << "\n";
    return 1;
  }
  Analyzer analyzer;
  AnalysisReqs data = {Args.filenames, Args.flags};
  Analysis analysis = analyzer.Analyze(data);
  if (!analysis.success) {
    std::cout << analysis.error_message << "\n";
    return 2;
  }
  for (std::string_view line : analysis.matches) {
    std::cout << line << "\n";
  }
  return 0;
}