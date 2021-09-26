#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  set<char> container;
  int helper(const string& s, int i) {
    int ret = 0;
    container.clear();
    for (int j = i; j >= 0; --j) {
      if (container.count(s[j]) > 0) {
        container.clear();
        break;
      };
      container.insert(s[j]);
      ret += 1;
    }
    return ret;
  }
  int lengthOfLongestSubstring(string s) {
    if (s.empty()) return 0;
    vector<int> dp(s.size() + 1, 1);
    for (int i = 1; i < s.size(); ++i) {
      dp[i] = std::max(dp[i - 1], helper(s, i));
    }
    return dp[s.size() - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.lengthOfLongestSubstring("adcabcbb");
  LOG(INFO) << ret;
  return 0;
}
