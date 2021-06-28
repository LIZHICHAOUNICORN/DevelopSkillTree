#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using std::vector;
using std::max;

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp (nums1.size() + 1, vector<int>(nums2.size() + 1, 0)); 
        int result = 0;
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) { 
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1; 
                }
                if (dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};




int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
