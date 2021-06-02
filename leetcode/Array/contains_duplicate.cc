#include <vector>
#include <cstdlib>
#include <set>

#include "glog/logging.h"
#include "gflags/gflags.h"

#include <gperftools/profiler.h>

DEFINE_int32(input_size, 10, "input data size");
DEFINE_int32(epolls, 100, "input data size");
DEFINE_string(porf_file, "move_zeroes.porf", "");

using namespace std;

class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    return nums.size() > set<int>(nums.begin(), nums.end()).size();
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int data[] = {0, 1, 0, 3, 12};
  vector<int> input_value(data, data + sizeof(data)/sizeof(int));
  Solution solu;
  bool ret = solu.containsDuplicate(input_value);
  LOG(INFO) << ret;
  return 0;
}
