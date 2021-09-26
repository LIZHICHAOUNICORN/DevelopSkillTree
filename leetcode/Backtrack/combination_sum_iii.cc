#include <iostream>
#include <vector>

using std::vector;

// backtrack version 1
class Solution {
 private:
  void backtrack(int target_sum, int k, int sum, int start) {
    if (path.size() == k) {
      if (target_sum == sum) result.push_back(path);
      return;
    }

    for (int i = start; i <= 9; ++i) {
      sum += i;
      path.push_back(i);
      backtrack(target_sum, k, sum, i + 1);
      sum -= i;
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> result;
  vector<int> path;
  vector<vector<int>> combinationSum3(int k, int n) {
    backtrack(n, k, 0, 1);
    return result;
  }
};

// backtrack version 2, cutoff version
class Solution {
 private:
  void backtrack(int target_sum, int k, int sum, int start) {
    if (sum > target_sum) {
      return;
    }
    if (path.size() == k) {
      if (target_sum == sum) result.push_back(path);
      return;
    }

    for (int i = start; i <= 9; ++i) {
      sum += i;
      path.push_back(i);
      backtrack(target_sum, k, sum, i + 1);
      sum -= i;
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> result;
  vector<int> path;
  vector<vector<int>> combinationSum3(int k, int n) {
    backtrack(n, k, 0, 1);
    return result;
  }
};

int main(int argc, char *argv[]) {
  Solution solu;
  vector<int> nums({1, 1, 1, 1, 1});
  return 0;
}
