#include "leetcode/String/Algorithms/kmp.h"

#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

// source from: https://www.zhihu.com/question/21923021

// 暴力构建next数组
// O(len(pattern)^2)
void KMP::BuildNext(const std::string& pattern) {
  next_.clear();
  next_.resize(pattern.size());
  for (int i = 1; i < pattern.size(); ++i) {
    int start = 0;
    int end = i;
    for (int len = 1; len < end - start; ++len) {
      const std::string& prefix = pattern.substr(start, len);
      int e_start = end - len + 1;
      const std::string& suffix = pattern.substr(e_start, len);
      if (prefix == suffix) {
        next_[i] = std::max(next_[i], len);
        continue;
      }
      break;
    }
  }
}

// O(len(pattern))
void KMP::FastBuildNext(const std::string& pattern) {
  next_.clear();
  int now = 0;
  next_.push_back(0);
  for (int i = 1; i < pattern.size(); ) {
    if (pattern[i] == pattern[now]) {
      now += 1;
      i += 1;
      next_.push_back(now);
    } else if (now != 0) {
      now = next_[now - 1];
    } else {
      next_.push_back(0);
      i += 1;
    }
  }
}


void KMP::Search(const std::string& src, const std::string& pattern,
                 std::vector<int>& result) {
  FastBuildNext(pattern);
  for (int s_s = 0, p_s = 0; s_s < src.size();) {
    if (src[s_s] == pattern[p_s]) {
      s_s += 1;
      p_s += 1;
    } else if (p_s != 0) {
      p_s = next_[p_s - 1];
    } else {
      s_s += 1;
    }
    if (p_s == pattern.size()) {
      result.push_back(s_s - p_s);
      p_s = next_[p_s-1];
    }
  }
}

}  // namespace base
