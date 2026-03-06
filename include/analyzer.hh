#pragma once

#include "analysis.hh"

#include <string>
#include <vector>
#include <utility>
#include <optional>

class Analyzer {

  private:
    bool loadFile(std::string_view filename, std::string& buffer);
  public:
    Analysis Analyze(AnalysisReqs reqs);
  
};