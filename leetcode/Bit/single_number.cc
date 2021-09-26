#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int ret = 0;
    for (auto e : nums) ret ^= e;
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int data[] = {2, 7, 11, 15};
  vector<int> input(data, data + sizeof(data) / sizeof(int));
  Solution solu;
  int ret = solu.singleNumber(input, FLAGS_input_size);
  return 0;
}
