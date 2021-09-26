// Author: Zhichao Li
// Time: 2021年06月19日

#include <vector>
using std::vector;

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    for (auto& num : nums) {
      int x = (num - 1) % n;
      nums[x] += n;
    }
    vector<int> ret;
    for (int i = 0; i < n; i++) {
      if (nums[i] <= n) {
        ret.push_back(i + 1);
      }
    }
    return ret;
  }
};

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> mem(nums.size() + 1, 0);
    for (int i = 0; i < nums.size(); ++i) {
      mem[nums[i]] += 1;
    }
    vector<int> ret;
    for (int j = 1; j < mem.size(); ++j) {
      if (mem[j] == 0) {
        ret.push_back(j);
      }
    }
    return ret;
  }
};
