#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/fizz-buzz/

class Solution {
 public:
  vector<string> fizzBuzz(int n) {
    vector<string> ret;
    for (int i = 1; i <= n; ++i) {
      if (i % 3 == 0 && i % 5 == 0) {
        ret.push_back("FizzBuzz");
        continue;
      }
      if (i % 3 == 0) {
        ret.push_back("Fizz");
        continue;
      }
      if (i % 5 == 0) {
        ret.push_back("Buzz");
        continue;
      }
      ret.emplace_back(std::to_string(i));
    }
    return ret;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  auto ret = solu.fizzBuzz(15);
  for (auto &r : ret) {
    LOG(INFO) << r;
  }
  return 0;
}
