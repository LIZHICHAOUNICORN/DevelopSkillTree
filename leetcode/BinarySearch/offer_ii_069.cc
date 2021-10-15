#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

// Problem: https://leetcode-cn.com/problems/B1IidL/

// 暴力法
class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    for (int i = 1, j = 2; j < arr.size(); ++j, ++i) {
      if (arr[j] < arr[i] && arr[i] > arr[i - 1]) return i;
    }
    return -1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> test_case({3, 4, 5, 1});

  Solution1 solu;
  int ret = solu.peakIndexInMountainArray(test_case);
  LOG(INFO) << ret;
  return 0;
}
