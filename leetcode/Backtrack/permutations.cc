#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::set;
class Solution {
 private:
    vector<vector<int>> result;
    vector<int> path;
    void backtrack(vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, used);
            path.pop_back();
            used[i] = false;
        }

    }
 public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtrack(nums, used);
        return result;
    }
};

int main(int argc, char *argv[]) {
  vector<int> nums({2,3,5});
  int target = 8;
  Solution solu;
  
  return 0;
}
