#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::string;

// greedy
class Solution {
 public:
  int monotoneIncreasingDigits(int n) {
    string str_num = to_string(n);
    int flag = str_num.size();
    for (int i = str_num.size() - 1; i > 0; --i) {
      if (str_num[i - 1] > str_num[i]) {
        str_num[i - 1]--;
        flag = i;
      }
    }
    for (int j = flag; j < str_num.size(); ++j) {
      str_num[j] = '9';
    }
    return stoi(str_num);
  }
};

// broute, failed
class Solution {
 private:
  bool checksum(int n) {
    int pre = n % 10;
    n = n / 10;
    while (n) {
      int cur = n % 10;
      if (pre < cur) return false;
      pre = cur;
      n = n / 10;
    }
    return true;
  }

 public:
  int monotoneIncreasingDigits(int n) {
    for (int i = n; i >= 0; --i) {
      if (checksum(i)) {
        return i;
      }
    }
    return 0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
