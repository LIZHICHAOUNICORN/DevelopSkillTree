#include <iostream>
#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;


class Solution {
public:
    int cuttingRope(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 0;
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
             int sub_result = 0;
             for (int j = 1; j <= i/2; ++j) {
                 int factor_a = max(j, dp[j]);
                 int factor_b = max(i-j, dp[i-j]);
                 sub_result = max(sub_result, factor_a*factor_b);
             }
             dp[i] = sub_result;
        }
        return dp[n];
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
