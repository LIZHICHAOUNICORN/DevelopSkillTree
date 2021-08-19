#include <vector>
#include <limits.h>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::min;

// respect
// https://leetcode-cn.com/problems/student-attendance-record-ii/solution/tong-ge-lai-shua-ti-la-yi-ti-liu-jie-dfs-s5fa/

// 暴力递归，超时
// Time O(3^n)
class Solution {
public:
    int reward_num;

    void GenerateReport(int report, const int n, int late_count, int absent_count) {
        // 结束条件
      if (report >= n) {
          if (late_count < 3 && absent_count < 2) {
              ++reward_num;
          }
          return;
      }
      // 本层逻辑
      if (late_count < 3 && absent_count < 2) {
          GenerateReport(report+1, n, 0, absent_count);
          GenerateReport(report+1, n, 0, absent_count+1);
          GenerateReport(report+1, n, late_count+1, absent_count);
      }

    }

    int checkRecord(int n) {
      if (n == 1) return 3;
      if (n == 2) return 8;
      GenerateReport(0, n, 0, 0);
      return reward_num%(static_cast<int>(std::pow(10,9)) + 7);
    }
};

// 暴力搜索 + 记忆化搜索
// Time: O(n*2*3), Space: O(n*2*3)
class Solution1 {
public:
    int reward_num;
    int MOD = 1000000007;

    int GenerateReport(int report, const int n, int late_count,
                       int absent_count, 
                       vector<vector<vector<int>>>& cache) {
        // 结束条件
        if (report >= n) {
                return 1;
        }
        // 本层逻辑
        if (cache[report][absent_count][late_count] > 0) {
            return cache[report][absent_count][late_count];
        }
        int ans = 0;
        ans += GenerateReport(report+1, n, 0, absent_count, cache);
        if (absent_count < 1) {
            ans += GenerateReport(report+1, n, 0, absent_count+1, cache);
            ans = ans % MOD;
        }
        if (late_count < 2) {
            ans += GenerateReport(report+1, n, late_count+1, absent_count, cache);
            ans = ans % MOD;
        }
        cache[report][absent_count][late_count] = ans;
        ans = ans % MOD;
        return ans;

    }

    int checkRecord(int n) {
        if (n == 1) return 3;
        if (n == 2) return 8;
        vector<vector<vector<int>>> cache(n, vector<vector<int>>(2, vector<int>(3, -1)));
        int reward_num = GenerateReport(0, n, 0, 0, cache);
        return reward_num%MOD;
    }
};


class Solution2 {
  int MOD = 1000000007;
 public:
   int checkRecord(int n) {
      vector<vector<vector<long>>> dp(n, vector<vector<long>>(2, vector<long>(3, 0)));
      dp[0][0][0] = 1;
      dp[0][1][0] = 1;
      dp[0][0][1] = 1;

      for (int i = 1; i < n; i++) {
          // 本次填入P，分成前一天累计了0个A和1个A两种情况
          dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;
          dp[i][1][0] = (dp[i - 1][1][0] + dp[i - 1][1][1] + dp[i - 1][1][2]) % MOD;
          // 本次填入A，前一天没有累计A都能转移过来
          // 这行可以与上面一行合并计算，为了方便理解，我们分开，下面会合并
          dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;
          // 本次填入L，前一天最多只有一个连续的L，分成四种情况
          dp[i][0][1] = dp[i - 1][0][0];
          dp[i][0][2] = dp[i - 1][0][1];
          dp[i][1][1] = dp[i - 1][1][0];
          dp[i][1][2] = dp[i - 1][1][1];
      }

      // 计算结果，即最后一天的所有状态相加
      long ans = 0;
      for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 3; j++) {
              ans = (ans + dp[n - 1][i][j]) % MOD;
          }
      }
      return static_cast<int>(ans);
  }
};

class Solution3 {
  int MOD = 1000000007;
 public:
  int checkRecord(int n) {
     vector<vector<long>> dp(2, vector<long>(3, 0));
     dp[0][0] = 1;
     dp[1][0] = 1;
     dp[0][1] = 1;
     for (int i = 1; i < n; ++i) {
       vector<vector<long>> cur(2, vector<long>(3, 0));
       // 当前插入P
       cur[0][0] = (dp[0][0] + dp[0][1] + dp[0][2]) % MOD;
       cur[1][0] = (dp[1][0] + dp[1][1] + dp[1][2]+ dp[0][0] + dp[0][1] + dp[0][2]) % MOD;
       // 当前插入A
       // cur[1][0] = (dp[0][0] + dp[0][1] + dp[0][2])%MOD;
       // 当前插入L
       cur[0][1] = dp[0][0];
       cur[0][2] = dp[0][1];
       cur[1][1] = dp[1][0];
       cur[1][2] = dp[1][1];
       dp.assign(cur.begin(), cur.end());
     }
     long ans = 0;
     for (int i = 0; i < 2; ++i) {
       for (int j = 0; j < 3; ++j) {
         ans = (ans + dp[i][j]) % MOD;
       }
     }
     return static_cast<int>(ans);
  }
};


int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  // vector<vector<int>> triangle = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
  // int ret = solu.minimumTotal(triangle);
  // LOG(INFO) << ret;

  return 0;
}
