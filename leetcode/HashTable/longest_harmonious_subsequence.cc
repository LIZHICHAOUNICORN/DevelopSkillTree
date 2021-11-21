#include <unordered_map>
#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/longest-harmonious-subsequence/

using namespace std;

// Hashtable
class Solution {
 public:
  int findLHS(vector<int>& nums) {
    unordered_map<int, int> cnt;
    int res = 0;
    for (int num : nums) {
      cnt[num]++;
    }
    // for (auto[key, val] : cnt) {
    for (auto& item: cnt) {
      auto& key = item.first;
      auto& val = item.second;
      if (cnt.count(key + 1)) {
        res = max(res, val + cnt[key + 1]);
      }
    }
    return res;
  }
};

// sort
class Solution1 {
 public:
  int findLHS(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int begin = 0;
    int res = 0;
    for (int end = 0; end < nums.size(); end++) {
      while (nums[end] - nums[begin] > 1) {
        begin++;
      }
      if (nums[end] - nums[begin] == 1) {
        res = max(res, end - begin + 1);
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> words({1, 3, 2, 2, 5, 2, 3, 7});

  Solution solu;
  auto ret = solu.findLHS(words);
  LOG(INFO) << ret;
  return 0;
}
