#include <algorithm>
#include <random>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_size, 0, "input data size");
using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() < 3) return res;
    std::sort(nums.begin(), nums.end());
    if (nums[0] > 0) return res;
    for (size_t i = 0; i < nums.size(); ++i) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      size_t head = i + 1;
      size_t tail = nums.size() - 1;
      while (head < tail) {
        vector<int> item;
        if (nums[i] + nums[head] + nums[tail] == 0) {
          item.push_back(nums[i]);
          item.push_back(nums[head]);
          item.push_back(nums[tail]);
          res.push_back(item);
          while (head < tail && nums[head] == nums[head + 1]) {
            head = head + 1;
          }
          while (head < tail && nums[tail] == nums[tail - 1]) {
            tail = tail - 1;
          }
          head += 1;
          tail -= 1;
        } else if (nums[i] + nums[head] + nums[tail] > 0) {
          tail -= 1;
        } else {
          head += 1;
        }
      }
    }
    return res;
  }
};

vector<vector<int>> three_sum(const vector<int>& input, int target) {
  vector<vector<int>> ret;
  unordered_map<int, pair<int, int>> index;
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = i + 1; j < input.size(); ++j) {
      index[input[i] + input[j]] = make_pair(i, j);
    }
  }
  for (size_t k = 0; k < input.size(); ++k) {
    if (index.find(target - input[k]) != index.end() &&
        index[target - input[k]].first != k &&
        index[target - input[k]].second != k) {
      vector<int> data;
      data.push_back(input[index[target - input[k]].first]);
      data.push_back(input[index[target - input[k]].second]);
      data.push_back(input[k]);
      ret.push_back(data);
      index.erase(target - input[k]);
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int data[] = {-1, 0, 1, 2, -1, -4};
  Solution solu;
  vector<int> input(data, data + sizeof(data) / sizeof(int));
  vector<vector<int>> ret = solu.threeSum(input);
  // vector<vector<int>> ret = three_sum(input, FLAGS_input_size);
  for (auto it : ret) {
    LOG(INFO) << "items:";
    for (auto key : it) {
      LOG(INFO) << key;
    }
  }
  return 0;
}
