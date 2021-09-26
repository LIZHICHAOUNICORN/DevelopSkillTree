#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::vector;
using std::set;

/*
 * @lc app=leetcode.cn id=40 lang=cpp
 *
 * [40] 组合总和 II
 */

class Solution {
 private:
  vector<vector<int>> result;
  vector<int> path;
  void backtrack(vector<int>& condidates, int target, int sum, int start_index,
                 vector<bool> used) {
    if (sum > target) return;
    if (sum == target) {
      result.push_back(path);
      return;
    }

    for (int i = start_index;
         i < condidates.size() && sum + condidates[i] <= target; ++i) {
      if (i > 0 && condidates[i] == condidates[i - 1] && used[i - 1] == false)
        continue;
      sum += condidates[i];
      path.push_back(condidates[i]);
      used[i] = true;
      backtrack(condidates, target, sum, i + 1, used);
      sum -= condidates[i];
      path.pop_back();
      used[i] = false;
    }
  }

 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<bool> used(candidates.size(), false);
    sort(candidates.begin(), candidates.end());
    backtrack(candidates, target, 0, 0, used);
    return result;
  }
};

int main(int argc, char* argv[]) {
  vector<int> nums({2, 3, 5});
  int target = 8;
  Solution solu;
  solu.combinationSum2(nums, target);

  return 0;
}
