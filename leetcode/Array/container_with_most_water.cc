#include <vector>
#include <cstdlib>
#include <random>

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

int most_water(vector<int>& input_value) {
  int ret = 0;
  for (size_t i = 0; i < input_value.size(); ++i) {
    for (size_t j = 1; j < input_value.size(); ++j) {
        int len = i > j ? i -j : j - i;
        int size = len * min(input_value[i], input_value[j]);
        ret = max(ret, size);
    }
  }
  return ret;
}

int most_water_v2(vector<int>& input_value) {
  size_t tail = input_value.size() - 1;
  size_t head = 0;
  size_t len = min(input_value[head], input_value[tail]);
  size_t ret = (tail - head) * len;
  for (; head < tail; ) {
    if (min(input_value[head], input_value[tail]) > static_cast<int> (len)) {
      ret = max(ret, (tail - head) * min(input_value[head], input_value[tail]));
    }
    // 短板前进
    input_value[head] > input_value[tail] ? --tail : ++head;
  }
  return ret;
}


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  random_device rd;
  int array_value[] = {1,8,6,2,5,4,8,3,7};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  int ret = 0;
  ret = most_water_v2(input_value);
  LOG(INFO) << "result: " << ret;
  return ret;
}
