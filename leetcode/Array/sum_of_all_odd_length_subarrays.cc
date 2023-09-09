#include <cstdlib>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;
// problem: https://leetcode-cn.com/problems/sum-of-all-odd-length-subarrays/

class Solution {
 public:
  int sumOddLengthSubarrays(vector<int>& arr) {
    if (arr.size() == 1) return arr[0];

    int size = arr.size();
    if (size % 2 == 0) {
      size = size - 1;
    }
    int ret = 0;
    for (int k = 1; k <= size; k = k + 2) {
      for (int i = 0; i <= size - k; ++i) {
        // 奇偶需要区别对待
        int end = k + i;
        if (arr.size() % 2 == 0) {
          end += 1;
        }
        for (int j = i; j < end; ++j) {
          ret += arr[j];
        }
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  vector<int> input_value(array_value,
                          array_value + sizeof(array_value) / sizeof(int));
  Solution solu;
  int ret = solu.sumOddLengthSubarrays(input_value);
  LOG(INFO) << "result: " << ret;
  return 0;
}
