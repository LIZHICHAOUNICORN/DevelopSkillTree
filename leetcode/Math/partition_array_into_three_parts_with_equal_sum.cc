#include <algorithm>
#include <climits>
#include <vector>
#include <cmath>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/construct-the-rectangle/

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int s = accumulate(A.begin(), A.end(), 0);
        if (s % 3 != 0) {
            return false;
        }
        int target = s / 3;
        int n = A.size(), i = 0, cur = 0;
        while (i < n) {
            cur += A[i];
            if (cur == target) {
                break;
            }
            ++i;
        }
        if (cur != target) {
            return false;
        }
        int j = i + 1;
        while (j + 1 < n) {  // 需要满足最后一个数组非空
            cur += A[j];
            if (cur == target * 2) {
                return true;
            }
            ++j;
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> sums({0,2,1,-6,6,-7,9,1,2,0,1});

  Solution solu;
  bool ret = solu.canThreePartsEqualSum(sums);
  LOG(INFO) << ret;

  return 0;
}
