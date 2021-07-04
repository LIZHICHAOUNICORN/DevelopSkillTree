#include <vector>
#include <cstdlib>
#include <random>

#include "glog/logging.h"
#include "gflags/gflags.h"

#include <gperftools/profiler.h>

DEFINE_int32(input_size, 10, "input data size");
DEFINE_int32(epolls, 100, "input data size");
DEFINE_string(porf_file, "move_zeroes.porf", "");

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int size = nums.size();
        vector<int> count(size+1, 0);
        int miss = 0;
        int repeat = 0;
        for (int i = 0; i < nums.size(); ++i) {
            count[nums[i]] += 1;
        }
        for (int j = 1; j < count.size(); ++j) {
            if (count[j] > 1) repeat = j;
            if (count[j] == 0) miss = j;
        }
        return {repeat,miss};
    }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
