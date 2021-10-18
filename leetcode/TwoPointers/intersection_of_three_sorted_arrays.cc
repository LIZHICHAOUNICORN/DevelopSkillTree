#include <iostream>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;

// Problem:
// https://leetcode-cn.com/problems/intersection-of-three-sorted-arrays/

class Solution {
 public:
  vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2,
                                 vector<int>& arr3) {
    int i = 0, j = 0, k = 0;
    vector<int> res;
    while (i < arr1.size() && j < arr2.size() && k < arr3.size()) {
      if (arr1[i] == arr2[j] && arr1[i] == arr3[k]) {
        res.emplace_back(arr1[i]);
      }
      int m = min({arr1[i], arr2[j], arr3[k]});
      if (arr1[i] == m) {
        ++i;
      }
      if (arr2[j] == m) {
        ++j;
      }
      if (arr3[k] == m) {
        ++k;
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.compareVersion("1.001", "1.1");
  LOG(INFO) << "ret " << ret;
  return 0;
}
