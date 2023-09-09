#include <string>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int i, j;
    for (i = 0; i < nums.size() - 1; i++) {
      for (j = i + 1; j < nums.size(); j++) {
        if (nums[i] + nums[j] == target) {
          return {i, j};
        }
      }
    }
    return {i, j};
  }
};

class Solution1 {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map<int, int> container;
    for (size_t i = 0; i < nums.size(); ++i) {
      container[nums[i]] = i;
    }
    for (int i = 0; i < nums.size(); ++i) {
      int other = target - nums[i];
      if (container[other] && i != container[other]) {
        return vector<int>({i, container[other]});
      }
    }
    return vector<int>({0, 1});
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> test_cast = {2, 7, 11, 15};
  Solution solu;
  vector<int> ret = solu.twoSum(test_cast, 9);
  return 0;
}
