#include "analyzer.hh"
#include "analysis.hh"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Private

bool Analyzer::loadFile(std::string_view filename, std::string& buffer){
  std::ifstream file(filename.data(), std::ios::binary | std::ios::ate);
  if (!file) { return false; }
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  buffer.resize(size);

  if (file.read(buffer.data(), size)) {
    return true;
  } else {
    return false;
  }
}

// Public

Analysis Analyzer::Analyze(AnalysisReqs reqs) {
  Analysis analysis;
  if (reqs.filenames.size() < 1) {
    analysis.success = false;
    analysis.error_message = "There is no filenames provided";
    return analysis;
  }
  std::string buffer;
  if (loadFile(reqs.filenames[0], buffer)) {
    bool pattern = false;
    std::string_view patternV;
    for (const auto& [flag, value] : reqs.flags) {
      if (flag == "--pattern") {
        pattern = true;
        patternV = value.value();
      }
    }
    std::string_view file = buffer;
    if (!pattern) {
      analysis.success = false;
      analysis.error_message = "There is no pattern flag";
      return analysis;
    }
    size_t pos = 0;
    size_t next_step = 0;

    analysis.matches.reserve(12000); 

    while((next_step = file.find('\n', pos)) != std::string::npos) {
      std::string_view line = file.substr(pos, next_step - pos);
      if (line.contains(patternV)) {
        analysis.matches.push_back(std::string(line));
      }
      pos = next_step + 1;
    }
    if (pos < file.size()) {
      std::string_view last_line = file.substr(pos);
      if (last_line.contains(patternV)) {
          analysis.matches.push_back(std::string(last_line));
      }
    }

  } else {
    analysis.success = false;
    analysis.error_message = "Problem in the loading phase";
  }
  return analysis;
}