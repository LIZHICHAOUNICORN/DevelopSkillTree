#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    if (nums.empty()) return;
    k = k % nums.size();
    int count = 0;
    for (int start = 0; count < nums.size(); ++start) {
      int cur = start;
      int prev = nums[start];
      do {
        int next = (cur + k) % nums.size();
        int temp = nums[next];
        nums[next] = prev;
        prev = temp;
        cur = next;
        count++;
      } while (start != cur);
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1, 2, 3, 4, 5, 6};
  vector<int> input_value(array_value,
                          array_value + sizeof(array_value) / sizeof(int));
  Solution solu;
  solu.rotate(input_value, 2);
  for (size_t i = 0; i < input_value.size(); ++i) {
    LOG(INFO) << input_value[i];
  }
  return 0;
}
