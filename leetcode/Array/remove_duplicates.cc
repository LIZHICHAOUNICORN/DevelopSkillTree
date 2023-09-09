#include <random>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_size, 0, "input data size");

using namespace std;

// not hard, but too much boundary condition
int remove_duplicates(vector<int>& sorted) {
  if (sorted.empty()) return 0;
  int length = 1;
  int dup_value = sorted[0];
  for (size_t i = 1, w_p = 1; i < sorted.size();) {
    // 找到第一个不是的位置
    int last_i = i;
    while (dup_value == sorted[i]) {
      ++i;
      if (i == sorted.size()) {
        break;
      }
    }
    // 更新重复值，重写值
    if (i != last_i && i < sorted.size()) {
      dup_value = sorted[i];
      sorted[w_p] = sorted[i];
      w_p += 1;
      length += 1;
    } else if (i < sorted.size()) {
      w_p += 1;
      length += 1;
      dup_value = sorted[i];
      i += 1;
    }
  }
  sorted.resize(length);
  return length;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int data[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  vector<int> sorted(data, data + sizeof(data) / sizeof(int));
  int ret = remove_duplicates(sorted);
  for (size_t i = 0; i < sorted.size(); ++i) {
    LOG(INFO) << sorted[i];
  }
  LOG(INFO) << "length: " << ret;
  return 0;
}
