#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      while (i > 0 && i < n && nums[i] == nums[i - 1]) {
          i++;
      }

      for (int j = i + 1; j < n; j++) {
        while (j != i + 1 && j < n && nums[j] == nums[j - 1]) {
            j++;
        }

        int l = j + 1, r = n - 1;

        while (l < r) {
          if (nums[i] + nums[j] + nums[l] + nums[r] == target) {
              res.push_back({nums[i], nums[j], nums[l], nums[r]});
              do { l++; } while (l < r && nums[l - 1] == nums[l]);
              do { r--; } while (l < r && nums[r] == nums[r + 1]);
          } else if (nums[i] + nums[j] + nums[l] + nums[r] < target) {
              do { l++; } while (l < r && nums[l - 1] == nums[l]);
          } else {
              do { r--; } while (l < r && nums[r] == nums[r + 1]);
          }
        }
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
