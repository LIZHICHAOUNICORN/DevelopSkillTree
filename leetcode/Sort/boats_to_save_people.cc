#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/boats-to-save-people
// TwoPointers
// Time: O(n*logn), space(logn)
class Solution {
 public:
  int numRescueBoats(vector<int>& people, int limit) {
    int ans = 0;
    sort(people.begin(), people.end());
    int light = 0, heavy = people.size() - 1;
    while (light <= heavy) {
      if (people[light] + people[heavy] > limit) {
        --heavy;
      } else {
        ++light;
        --heavy;
      }
      ++ans;
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  // Build test case.
  vector<int> people({5, 1, 4, 2});

  Solution solu;
  int ret = solu.numRescueBoats(people, 6);
  LOG(INFO) << "result: " << ret;
  return 0;
}
