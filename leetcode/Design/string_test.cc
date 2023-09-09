#include "leetcode/Design/string.h"
#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  base::String str;
  std::cout << str.size() << std::endl;

  const char* test = "copy from cstring";
  base::String cp_test(test);

  std::cout << cp_test << std::endl;
  // cp_test = "copy from string";
  // std::cout << cp_test << std::endl;
  base::String cp_string(cp_test);
  std::cout << cp_string << std::endl;

  base::String cp_other = cp_string;
  std::cout << cp_other << std::endl;

  base::String mv_str(std::move(cp_other));
  std::cout << mv_str << std::endl;

  return 0;
}
