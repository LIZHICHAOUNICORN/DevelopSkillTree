#include <vector>
#include <unordered_map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

// backtrack
class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    backtrack(nums,res,0);
    return res;
  }

  void swap(int &a,int &b) {
    int temp;
    temp=a;
    a=b;
    b=temp;
  }

  void backtrack(vector<int> &nums,vector<vector<int>> &res,int i) {
    if(i==nums.size()) res.push_back(nums);
    for(int j = i; j < nums.size() ; j++){
      swap(nums[i],nums[j]);
      backtrack(nums,res,i+1);
      swap(nums[i],nums[j]);
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> input = {1, 2};
  vector<vector<int>> ret = solu.permute(input);
  return 0;
}
