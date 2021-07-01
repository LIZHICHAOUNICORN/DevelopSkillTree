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
    void backtrack(vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i-1] && used[i-1] == false) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true;
                path.push_back(nums[i]);
                backtrack(nums, used);
                used[i] = false;
                path.pop_back();
            }
        }

    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());
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
