#include <array>
#include <locale>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/to-lower-case/

class Solution {
 public:
  string toLowerCase(string s) {
    for (char& ch : s) {
      if (ch >= 65 && ch <= 90) {
        ch += 32;
      }
    }
    return s;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string licensePlate("sPSt");
  Solution solu;
  string ret = solu.toLowerCase(licensePlate);
  LOG(INFO) << ret;
  return 0;
}
