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

int find_non_zero(vector<int>& input_value, int start) {
  int pos = -1;
  for (size_t i = start; i < input_value.size(); ++i) {
    if (input_value[i] != 0) return i;
  }
  return pos;
}

void move_zeroes(vector<int>& input_value) {
  bool stop = false;
  while(!stop) {
    for (size_t i = 0; i < input_value.size(); ++i) {
      if (input_value[i] == 0) {
        int pos = find_non_zero(input_value, i);
        if (pos == -1) {
          stop = true;
          break;
        }
        input_value[i] = input_value[pos];
        input_value[pos] = 0;
      }
    }
  } 
}


class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};





int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // ProfilerStart(FLAGS_porf_file.c_str());
  for (int i = 0; i < FLAGS_epolls; ++i) {
    random_device rd;
    int data[] = {0, 1, 0, 3, 12};
    vector<int> input_value(data, data + sizeof(data)/sizeof(int));
    move_zeroes(input_value);
    for (auto it : input_value) {
      LOG(INFO) << it;
    }
  }
  // ProfilerStop();
  return 0;
}
