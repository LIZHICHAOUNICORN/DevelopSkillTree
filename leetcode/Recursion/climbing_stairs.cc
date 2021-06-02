#include <vector>
#include <unordered_map>

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(input_num, 45, "the input value");

using namespace std;

class Solution {
 public:
  int climbStairs(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    unordered_map<int, int> cache;
    cache[1] = 1;
    cache[2] = 2;
    int ret = helper(n, cache);
    return ret;
  }
 private:
  int helper(int n, unordered_map<int, int>& cache) {
    if (cache.find(n) != cache.end()) return cache[n];
    cache[n] = helper(n-1, cache) + helper(n-2, cache);
    return cache[n];
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  string usage = "climb_stair --input_num=44 --logtostderr";
  gflags::SetUsageMessage(usage);
  Solution solu;
  int ret = solu.climbStairs(FLAGS_input_num);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
