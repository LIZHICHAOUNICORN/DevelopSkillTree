#include <vector>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int mid = 0;
        int l = 0;
        int r = nums.size() -1;
        while (l <= r) {
            mid = (l+r)/2;
            if (nums[mid] == target) break;
            if (nums[mid] > target) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (nums[mid] != target) return -1;
        return mid;

    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums({5,7,8,10});
  solu.search(nums, 8);
  return 0;
}
