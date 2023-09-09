#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int start = 0;
    int end = numbers.size() - 1;
    while (start < end) {
      if (numbers[start] + numbers[end] == target) {
        return {start + 1, end + 1};
      }
      if (numbers[start] + numbers[end] > target) {
        end = end - 1;
      } else {
        start = start + 1;
      }
    }
    return {start + 1, end + 1};
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums({5, 7, 8, 10});
  solu.twoSum(nums, 12);
  return 0;
}
