#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::sort;
using namespace std;

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> left(n);
    for (int i = 0; i < n; i++) {
      if (i > 0 && ratings[i] > ratings[i - 1]) {
        left[i] = left[i - 1] + 1;
      } else {
        left[i] = 1;
      }
    }
    int right = 0, ret = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (i < n - 1 && ratings[i] > ratings[i + 1]) {
        right++;
      } else {
        right = 1;
      }
      ret += max(left[i], right);
    }
    return ret;
  }
};

class Solution1 {
 public:
  int candy(vector<int>& ratings) {
    vector<int> cy(ratings.size(), 1);
    for (int i = 1; i < ratings.size(); ++i) {
      if (ratings[i] > ratings[i - 1]) cy[i] = cy[i - 1] + 1;
    }
    for (int j = ratings.size() - 2; j >= 0; --j) {
      if (ratings[j] > ratings[j + 1]) cy[j] = max(cy[j + 1] + 1, cy[j]);
    }
    int result = 0;
    for (int k = 0; k < ratings.size(); ++k) {
      result += cy[k];
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> ratings({2, 1, 0, 3, 2, 3});
  Solution solu;
  int ret = solu.candy(ratings);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
