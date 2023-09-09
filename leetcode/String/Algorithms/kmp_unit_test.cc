#include "leetcode/String/Algorithms/kmp.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(src, "asdfadsfasdfabcabd", "src string");
DEFINE_string(pattern, "abcabd", "pattern string");

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  std::vector<int> ret;

  base::KMP kmp;
  kmp.Search(FLAGS_src, FLAGS_pattern, ret);
  for (auto it : ret) {
    LOG(INFO) << "pos: " << it;
  }
  return 0;
}
