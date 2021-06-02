#include <vector>
#include <unordered_map>
#include <random>

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

vector<int> two_sum(const vector<int>& input, int target) {
  vector<int> ret;
  unordered_map<int, int> index;
  for (size_t i = 0; i < input.size(); ++i) {
    index[input[i]] = i;
  }
  for (auto it : input) {
    if (index.find(target - it) != index.end()) {
      ret.push_back(it);
      ret.push_back(target - it);
      LOG(INFO) << "first: " << it << ", second: " << target - it;
      index.erase(it);
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int data[] = {2, 7, 11, 15};
  vector<int> input(data, data + sizeof(data)/sizeof(int));
  vector<int> ret = two_sum(input, FLAGS_input_size);
  return 0;
}
