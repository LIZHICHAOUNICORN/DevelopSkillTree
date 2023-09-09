#include <climits>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    int n = arr.size();
    int left = 1, right = n - 2, ans = 0;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (arr[mid] > arr[mid + 1]) {
        ans = mid;
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> arr({0, 2, 1, 0});
  Solution solu;
  int ret = solu.peakIndexInMountainArray(arr);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
