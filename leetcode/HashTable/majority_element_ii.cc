#include <string>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problems: https://leetcode-cn.com/problems/majority-element-ii/

using namespace std;

// Hashtable
class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
    unordered_map<int, int> cnt;

    for (auto& v : nums) {
      cnt[v]++;
    }
    for (auto& v : cnt) {
      if (v.second > n / 3) {
        ans.push_back(v.first);
      }
    }

    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({3,2,3});
  Solution solu;
  auto ret = solu.findRepeatedDnaSequences(nums);
  LOG(INFO) << ret.back();
  return 0;
}
