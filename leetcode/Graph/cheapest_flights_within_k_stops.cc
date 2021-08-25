#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/cheapest-flights-within-k-stops

// dfs + cache
class Solution {
 private:
  int INF = 1000007;
 public:
   int dfs(vector<vector<int>>& flights, int src, int dst, int k, vector<vector<int>>& memo) {
     if (k < 0) return INF;
     if (src == dst) return 0;
     if (memo[src][k] != 0) return memo[src][k];
     int min_value = INF;
     for (auto flight : flights) {
       if (flight[0] == src) {
         min_value = min(min_value, dfs(flights, flight[1], dst, k-1, memo)+flight[2]);
       }
     }
     memo[src][k] = min_value;
     return min_value;
   }

   int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
     vector<vector<int>> memo(n, vector<int>(k+2, 0));
     int ans = dfs(flights, src, dst, k+1, memo);
     return ans > INF ? -1 : ans;
   }
};

// DP
class Solution1 {
 private:
  int INF = 100007;

 public:
  int FillDp(int n, vector<vector<int>>flights, int src, int dst, int k) {
     vector<vector<int>> dp(n, vector<int>(k+2, INF));
     dp[dst][0] = 0;
     for (int i = 1; i <= k+1; ++i) {
       for (auto flight : flights) {
         dp[flight[0]][i] = min(dp[flight[0]][i], dp[flight[1]][i-1]+flight[2]);
       }
     }
     auto ans = std::min_element(dp[src].begin(), dp[src].end());
     return *ans;
  }
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    int ret = FillDp(n, flights, src, dst, k);
    return  ret >= INF ? -1 : ret;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // Build test case.
  vector<vector<int>> flights;
  vector<int> flight1({0,1,100});
  vector<int> flight2({1,2,100});
  vector<int> flight3({0,2,500});
  flights.push_back(flight1);
  flights.push_back(flight2);
  flights.push_back(flight3);

  Solution solu;
  int ret = solu.findCheapestPrice(3, flights, 0, 2, 0);
  LOG(INFO) << "result: " << ret;
  Solution1 solu1;
  int ret1 = solu1.findCheapestPrice(3, flights, 0, 2, 0);
  LOG(INFO) << "result: " << ret1;
  return 0;
}
