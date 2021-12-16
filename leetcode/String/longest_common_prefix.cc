#include <algorithm>
#include <array>
#include <locale>
#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/longest-common-prefix/

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (!strs.size()) {
      return "";
    }
    string prefix = strs[0];
    int count = strs.size();
    for (int i = 1; i < count; ++i) {
      prefix = longestCommonPrefix(prefix, strs[i]);
      if (!prefix.size()) {
        break;
      }
    }
    return prefix;
  }

  string longestCommonPrefix(const string& str1, const string& str2) {
    int length = min(str1.size(), str2.size());
    int index = 0;
    while (index < length && str1[index] == str2[index]) {
      ++index;
    }
    return str1.substr(0, index);
  }
};

class Solution1 {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (!strs.size()) {
      return "";
    } else {
      return longestCommonPrefix(strs, 0, strs.size() - 1);
    }
  }

  string longestCommonPrefix(const vector<string>& strs, int start, int end) {
    if (start == end) {
      return strs[start];
    } else {
      int mid = (start + end) / 2;
      string lcpLeft = longestCommonPrefix(strs, start, mid);
      string lcpRight = longestCommonPrefix(strs, mid + 1, end);
      return commonPrefix(lcpLeft, lcpRight);
    }
  }

  string commonPrefix(const string& lcpLeft, const string& lcpRight) {
    int minLength = min(lcpLeft.size(), lcpRight.size());
    for (int i = 0; i < minLength; ++i) {
      if (lcpLeft[i] != lcpRight[i]) {
        return lcpLeft.substr(0, i);
      }
    }
    return lcpLeft.substr(0, minLength);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> strs({"flower", "flow", "flight"});

  Solution solu;
  auto ret = solu.longestCommonPrefix(strs);
  LOG(INFO) << ret;
  return 0;
}
