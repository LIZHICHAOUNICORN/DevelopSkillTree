#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::sort;

class Solution {
 public:
  vector<int> partitionLabels(string s) {
    int hash[27] = {0};
    for (int i = 0; i < s.size(); ++i) {
      hash[s[i] - 'a'] = i;
    }
    vector<int> result;
    int left = 0;
    int right = 0;
    for (int i = 0; i < s.size(); ++i) {
      right = max(right, hash[s[i] - 'a']);
      if (i == right) {
        result.push_back(right - left + 1);
        left = i + 1;
      }
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
