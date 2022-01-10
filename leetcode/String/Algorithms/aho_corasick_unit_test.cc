#include "leetcode/String/Algorithms/aho_corasick.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  std::vector<std::string> words({"he", "she", "hers", "his", "shy", "ghj", "adfads"});

  std::string pattern("ahishersdsaffadsfasdfafsdfaswefcxagdwertyujkfghjvbn");

  base::AhoCorsick ac;
  auto ret = ac.multiSearch(pattern, words);
  LOG(INFO) << pattern << " found ";
  for (const std::pair<int, int>& it : ret) {
    LOG(INFO) << pattern.substr(it.first, it.second);
  }

  return 0;
}
