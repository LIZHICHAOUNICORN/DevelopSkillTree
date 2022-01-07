#include "leetcode/String/Algorithms/sunday.h"

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace base {

// From:
// https://leetcode-cn.com/problems/implement-strstr/solution/python3-sundayjie-fa-9996-by-tes/

int Sunday::Search(const std::string& haystack, const std::string& needle) {
  // 建立偏移表
  int h_size = haystack.size();
  int n_size = needle.size();
  unordered_map<char, int> next_step;
  for (int i = 0; i < n_size; i++) {
    next_step[needle[i]] = n_size - i;
  }

  // 遍历
  int i = 0;
  while (i <= h_size - n_size) {
    if (haystack.substr(i, n_size) == needle)
      return i;
    else {
      // 查询substr后的字符的偏移值
      if (i + n_size > h_size - 1)
        return -1;
      else {
        if (next_step.find(haystack[i + n_size]) != next_step.end()) {
          i += next_step[haystack[i + n_size]];
        } else {
          i += n_size + 1;
        }
      }
    }
  }
  return -1;
}

}  // namespace base
