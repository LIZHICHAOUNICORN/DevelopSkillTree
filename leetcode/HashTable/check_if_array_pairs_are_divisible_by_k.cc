#include <algorithm>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem:
// https://leetcode-cn.com/problems/check-if-array-pairs-are-divisible-by-k/

using namespace std;

// Hashtable

class Solution {
 public:
  bool canArrange(vector<int>& arr, int k) {
    unordered_map<int, int> mod;
    for (int num : arr) {
      ++mod[(num % k + k) % k];
    }
    for (auto[t, occ] : mod) {
      if (t > 0 && (!mod.count(k - t) || mod[k - t] != occ)) {
        return false;
      }
    }
    return mod[0] % 2 == 0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> words({1, 2, 3, 4, 5, 10, 6, 7, 8, 9, 11, 19});

  Solution solu;
  auto ret = solu.canArrange(words, 5);
  LOG(INFO) << ret;
  return 0;
}
