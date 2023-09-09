#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/subarray-sum-equals-k/submissions/
// Solutions:
// https://leetcode-cn.com/problems/subarray-sum-equals-k/solution/he-wei-kde-zi-shu-zu-by-leetcode-solution/

class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int len = nums.size();
    int ret = 0;
    for (int start = 0; start < len; ++start) {
      for (int end = start; end < len; ++end) {
        int sum = 0;
        for (int k = start; k <= end; ++k) {
          sum += nums[k];
        }
        if (sum == k) ret += 1;
      }
    }
    return ret;
  }
};

// 暴力优化
class Solution2 {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    for (int start = 0; start < nums.size(); ++start) {
      int sum = 0;
      for (int end = start; end >= 0; --end) {
        sum += nums[end];
        if (sum == k) {
          count++;
        }
      }
    }
    return count;
  }
};

// 前缀和
class Solution3 {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    vector<int> prefix_sum(nums.size(), 0);
    for (int i = 1; i < prefix_sum.size(); ++i) {
      prefix_sum[i] = nums[i] + prefix_sum[i - 1];
    }
    for (int start = 0; start < nums.size(); ++start) {
      for (int end = start; end <= nums.size(); ++end) {
        if (prefix_sum[end + 1] - prefix_sum[start] == k) {
          count++;
        }
      }
    }
    return count;
  }
};

// 前缀和 + hash
class Solution4 {
 public:
  int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;
    int count = 0, pre = 0;
    for (auto& x : nums) {
      pre += x;
      if (mp.find(pre - k) != mp.end()) {
        count += mp[pre - k];
      }
      mp[pre]++;
    }
    return count;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  vector<int> nums({1, 1, 1});
  int ret = solu.subarraySum(nums, 2);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
