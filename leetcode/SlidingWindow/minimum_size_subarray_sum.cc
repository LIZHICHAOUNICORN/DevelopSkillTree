#include <string>
#include <vector>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problems: https://leetcode-cn.com/problems/minimum-size-subarray-sum/
// Solutions:
// https://leetcode-cn.com/problems/minimum-size-subarray-sum/solution/chang-du-zui-xiao-de-zi-shu-zu-tu-jie-sh-ae80/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT_MAX;
        int sum = 0;
        for(int i = 0, j = 0; i < nums.size(); i++)
        {
            sum += nums[i];     //向右扩展窗口
            while(sum - nums[j] >= target) sum -= nums[j++]; //向左收缩窗口
            if(sum >= target)  res = min(res, i - j + 1);    //区间更新
        }
        return res == INT_MAX ? 0 : res;    
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string ret = solu.minWindow("ADOBECODEBANC", "ABC");

  LOG(INFO) << ret;
  return 0;
}
