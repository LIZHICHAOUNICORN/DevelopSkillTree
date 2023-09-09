#include <limits.h>
#include <algorithm>
#include <deque>
#include <stack>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// comments:
// https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/
// NOLINT

class Solution {
 public:
  int shortestSubarray(vector<int>& nums, int k) {
    if (nums.empty()) return -1;
    int n = nums.size();

    std::vector<long> presum(n + 1);
    for (int i = 1; i <= n; ++i) presum[i] = presum[i - 1] + nums[i - 1];

    int min_len = n + 1;

    std::deque<int> deq;
    for (int j = 0; j <= n; ++j) {
      while (!deq.empty() && presum[j] < presum.at(deq.back())) deq.pop_back();

      while (!deq.empty() && presum[j] - presum.at(deq.front()) >= k) {
        min_len = std::min(min_len, j - deq.front());
        deq.pop_front();
      }

      deq.push_back(j);
    }
    return min_len == n + 1 ? -1 : min_len;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int k = 3;
  vector<int> input_value({2, -1, 2});

  Solution solu;
  auto ret = solu.shortestSubarray(input_value, k);
  LOG(INFO) << ret;
  return 0;
}
