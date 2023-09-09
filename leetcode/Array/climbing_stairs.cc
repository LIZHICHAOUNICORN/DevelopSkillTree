#include <cstdlib>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

int climbing_stairs(size_t floor) {
  int ret = 0;
  if (floor <= 2) return floor;
  int one = 1;
  int two = 2;
  for (size_t i = 3; i < floor; ++i) {
    ret = one + two;
    one = two;
    two = ret;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int floor = FLAGS_input_size;
  int ret = climbing_stairs(floor);
  LOG(INFO) << "return: " << ret;
  return ret;
}
