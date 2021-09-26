#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::vector;
using std::set;

// failed. test case: [2,3,5]\n 8
class Solution {
 private:
  void backtrack(int sum, int target, vector<int>& condidates) {
    if (sum >= target) {
      if (sum == target) {
        std::sort(path.begin(), path.end());
        if (!container.count(path)) {
          std::cout << "sum: " << sum << ", target: " << target << std::endl;
          for (auto i : path) {
            std::cout << i << " ";
          }
          std::cout << std::endl;
          container.insert(path);
          result.push_back(path);
        }
      }
      return;
    }
    for (int i = 0; i < condidates.size(); ++i) {
      path.push_back(condidates[i]);
      sum += condidates[i];
      backtrack(sum, target, condidates);
      path.pop_back();
      sum -= condidates[i];
    }
  }

 public:
  vector<int> path;
  vector<vector<int>> result;
  set<vector<int>> container;
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    backtrack(0, target, candidates);
    return result;
  }
};

class Solution1 {
 private:
  void backtrack(int sum, int target, vector<int>& condidates, int index) {
    if (sum >= target) {
      if (sum == target) {
        // sort(path.begin(), path.end());
        // if (!container.count(path)) {
        //    container.insert(path);
        result.push_back(path);
        //}
      }
      return;
    }
    for (int i = index; i < condidates.size(); ++i) {
      path.push_back(condidates[i]);
      sum += condidates[i];
      backtrack(sum, target, condidates, i);
      path.pop_back();
      sum -= condidates[i];
    }
  }

 public:
  vector<int> path;
  vector<vector<int>> result;
  // set<vector<int>> container;
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    backtrack(0, target, candidates, 0);
    return result;
  }
};

int main(int argc, char* argv[]) {
  vector<int> nums({2, 3, 5});
  int target = 8;
  Solution solu;
  solu.combinationSum(nums, target);

  return 0;
}
