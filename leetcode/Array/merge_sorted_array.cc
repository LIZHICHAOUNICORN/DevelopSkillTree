#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> ret;
    size_t m_index = 0, n_index = 0;
    for (; m_index < m && n_index < n;) {
      if (nums1[m_index] > nums2[n_index]) {
        ret.push_back(nums2[n_index]);
        ++n_index;
      } else {
        ret.push_back(nums1[m_index]);
        ++m_index;
      }
    }
    for (; m_index < m; ++m_index) {
      ret.push_back(nums1[m_index]);
    }
    for (; n_index < n; ++n_index) {
      ret.push_back(nums2[n_index]);
    }
    for (size_t i = 0; i < m + n; ++i) {
      nums1[i] = ret[i];
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1, 2, 3, 4, 5, 6};
  vector<int> input_value(array_value,
                          array_value + sizeof(array_value) / sizeof(int));
  return 0;
}
