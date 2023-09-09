#include <string>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/next-greater-element-i/

using namespace std;

// Hashtable
class Solution {
 public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ret;
    if (nums1.empty()) return ret;

    unordered_map<int, int> cache;
    for (int i = 0; i < nums2.size(); ++i) {
      cache[nums2[i]] = i;
    }

    for (int j = 0; j < nums1.size(); ++j) {
      int k = cache[nums1[j]];
      for (; k < nums2.size(); ++k) {
        if (nums2[k] > nums1[j]) {
          ret.push_back(nums2[k]);
          break;
        }
      }
      if (k == nums2.size()) {
        ret.push_back(-1);
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums1({1, 3, 4, 2});
  vector<int> nums2({4, 1, 2});

  Solution solu;
  auto ret = solu.nextGreaterElement(nums1, nums2);
  LOG(INFO) << ret.back();
  return 0;
}
