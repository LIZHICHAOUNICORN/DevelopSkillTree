#include <vector>

#include <glog/logging.h>
#include <gflags/gflags.h>


using namespace std;
// Problem: https://leetcode-cn.com/problems/reshape-the-matrix/

class Solution {
 public:
  vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
      int m = nums.size();
      int n = nums[0].size();
      if (m * n != r * c) {
          return nums;
      }

      vector<vector<int>> ans(r, vector<int>(c));
      for (int x = 0; x < m * n; ++x) {
          ans[x / c][x % c] = nums[x / n][x % n];
      }
      return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<vector<int>> input;
  vector<int> col1({0,1,0,0});
  vector<int> col2({1,1,1,0});
  vector<int> col3({0,1,0,0});
  vector<int> col4({1,1,0,0});
  input.push_back(col1);
  input.push_back(col2);
  input.push_back(col3);
  input.push_back(col4);

  Solution solu;
  auto ret = solu.matrixReshape(input, 2, 8);
  return 0;
}
