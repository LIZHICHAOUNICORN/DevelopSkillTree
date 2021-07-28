#include <vector>
#include <algorithm>

using std::lower_bound;
using std::vector;

// #include "glog/logging.h"
// #include "gflags/gflags.h"

DEFINE_int32(input, 8, "The test case");

class Solution {
public:
    int minOperations(vector<int> &target, vector<int> &arr) {
        int n = target.size();
        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) {
            pos[target[i]] = i;
        }
        vector<int> d;
        for (int val : arr) {
            if (pos.count(val)) {
                int idx = pos[val];
                auto it = lower_bound(d.begin(), d.end(), idx);
                if (it != d.end()) {
                    *it = idx;
                } else {
                    d.push_back(idx);
                }
            }
        }
        return n - d.size();
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.isPerfectSquare(FLAGS_input);
  LOG(INFO) << ret;
  return 0;
}
