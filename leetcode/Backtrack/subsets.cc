#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::vector;
using std::set;

class Solution {
 public:
  vector<vector<int>> result;
  vector<int> path;
  void backtrack(vector<int>& nums, int start_index, int count) {
    if (path.size() == count) {
      result.push_back(path);
      return;
    }
    for (int i = start_index; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      backtrack(nums, i + 1, count);
      path.pop_back();
    }
  }
  vector<vector<int>> subsets(vector<int>& nums) {
    for (int i = 0; i <= nums.size(); ++i) {
      backtrack(nums, 0, i);
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  vector<int> nums({2, 3, 5});
  int target = 8;
  Solution solu;

  return 0;
}
