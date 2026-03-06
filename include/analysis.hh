#pragma once

#include <string>
#include <vector>
#include <utility>
#include <optional>

struct Analysis {
  std::vector<std::string> matches;
  bool success = true;
  std::string_view error_message;
};

struct AnalysisReqs {
  std::vector<std::string_view> filenames;
  std::vector<std::pair<std::string_view, std::optional<std::string_view>>> flags;
};