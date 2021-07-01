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
    void backtrack(vector<int>& nums, int start_index) {
        if (path.size() > 1) {
            result.push_back(path);
        }
        unordered_set<int> used;
        for (int i = start_index; i < nums.size(); ++i) {
            if ((!path.empty() && path.back() > nums[i]) ||
                (used.find(nums[i]) != used.end())) {
                continue;
            }
            used.insert(nums[i]);
            path.push_back(nums[i]);
            backtrack(nums, i+1);
            path.pop_back();
        }
    }
  public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtrack(nums, 0);
        return result;
    }
};

// version 2, 使用数组来优化用set存储使用过的
class Solution1 {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtrack(vector<int>& nums, int start_index) {
        if (path.size() > 1) {
            result.push_back(path);
        }
        // unordered_set<int> used;
        int used[201] = {0};
        for (int i = start_index; i < nums.size(); ++i) {
            if ((!path.empty() && path.back() > nums[i]) ||
                (used[nums[i] + 100] == 1)) {
                continue;
            }
            // used.insert(nums[i]);
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtrack(nums, i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtrack(nums, 0);
        return result;
    }
};

int main(int argc, char *argv[]) {
  vector<int> nums({2,3,5});
  int target = 8;
  Solution solu;
  
  return 0;
}
