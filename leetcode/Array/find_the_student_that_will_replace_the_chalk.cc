#include <vector>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;
// problem: https://leetcode-cn.com/problems/find-the-student-that-will-replace-the-chalk/

class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();
        long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= total;
        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (chalk[i] > k) {
                res = i;
                break;
            }
            k -= chalk[i];
        }
        return res;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {5,1,5};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  Solution solu;
  int ret = solu.chalkReplacer(input_value, 22);
  LOG(INFO) << "result: " << ret;
  return 0;
}
