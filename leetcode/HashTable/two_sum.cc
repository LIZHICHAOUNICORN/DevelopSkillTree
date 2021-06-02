#include <unordered_map>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int i,j;
    for(i=0;i<nums.size()-1;i++)
    {
      for(j=i+1;j<nums.size();j++)
      {
        if(nums[i]+nums[j]==target)
        {
          return {i,j};
        }
      }
    }
    return {i,j};
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> test_cast = {2,7,11,15};
  Solution solu;
  vector<int> ret = solu.twoSum(test_cast, 9);
  return 0;
}
