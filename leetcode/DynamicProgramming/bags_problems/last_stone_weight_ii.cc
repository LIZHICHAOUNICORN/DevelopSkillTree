#include <algorithm>
#include <numeric>
#include <vector>

using std::vector;

// basic version
class Solution {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    vector<int> dp((30 * 100 >> 1) + 1, 0);
    int sum = std::accumulate(stones.begin(), stones.end(), 0);
    int target = sum / 2;
    for (int i = 0; i < stones.size(); ++i) {
      for (int j = target; j >= stones[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - stones[i]] + stones[i]);
      }
    }

    return sum - dp[target] - dp[target];
  }
};

int main(int argc, char* argv[]) {
  Solution solu;
  return 0;
}
