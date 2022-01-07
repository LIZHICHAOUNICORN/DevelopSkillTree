#include "leetcode/String/Algorithms/boyer_moore.h"

#include <string>
#include <vector>

using namespace std;

namespace base {

// from: https://juejin.cn/post/6844903488854605831
// 计算bad charactor
// 利用哈希空间换时间的思想，使用字符作为下标而不是位置作为下标。这样只需要遍历一遍即可。如果是纯
// 8 位字符也只需要 256 个空间大小，而且对于大模式，可能本身长度就超过了
// 256，所以这样做是值得的（这也是为什么数据越大，BM 算法越高效的原因之一）
void BM::GetBadChar(const string& pattern, vector<int>& bad_char) {
  int len = pattern.size();
  // 搜索词中不存在坏字符，那就直接右移整个搜索词长度这么大步数。
  // 默认直接末尾
  for (int i = 0; i < 256; ++i) {
    bad_char.push_back(len);
  }
  // 搜索词中有对应的坏字符时，让搜索词中最靠右的对应字符与坏字符相对。
  for (int j = 0; j < len - 1; ++j) {
    const char& c = pattern[j];
    bad_char[c] = len - j - 1;
  }
}

void BM::GetSuff(const string& pattern, vector<int>& suff) {
  int len = pattern.size();
  for (int i = len - 2; i >= 0; i--) {
    int k = i;
    while (k >= 0 && pattern[k] == pattern[len - 1 - i + k]) k--;
    suff[i] = i - k;
  }
}

// 好后缀
void BM::GetGoodSuff(const string& pattern, vector<int>& good_suff) {
  int len = pattern.size();
  vector<int> suff(len + 1, 0);
  // suff存储子串的最长匹配长度.
  GetSuff(pattern, suff);
  // 初始化 当没有好后缀也没有公共前缀时
  // 3）如果完全不存在和好后缀匹配的子串，则右移整个搜索词。
  for (int i = 0; i < len; i++) good_suff[i] = len;

  // 2）如果不存在和好后缀完全匹配的子串，则优先选取长度最长且也属于前缀的那部分字符串。
  // 没有好后缀 有公共前缀 调用suff 但是要右移一位 类似KMP里的next数组
  for (int i = len - 1; i >= 0; i--) {
    if (suff[i] == i + 1) {
      for (int j = 0; j < len - 1; j++) {
        // 保证每个位置不会重复修改
        if (good_suff[j] == len) {
          good_suff[j] = len - 1 - i;
        }
      }
    }
  }
  // 1）搜索词中有子串和好后缀完全匹配，则将最靠右的那个子串移动到好后缀的位置继续进行匹配。
  // 有好后缀 有公共前缀
  for (int i = 0; i < len - 1; i++) {
    good_suff[len - 1 - suff[i]] = len - 1 - i;
  }
}

int BM::Search(const std::string& haystack, const std::string& needle) {
  int t_len = needle.size();
  int s_len = haystack.size();

  vector<int> bad_char;
  GetBadChar(needle, bad_char);

  vector<int> good_suff(t_len, 0);
  GetGoodSuff(needle, good_suff);

  int i = 0;
  while (i <= s_len - t_len) {
    int j = t_len - 1;
    while (j > -1 && haystack[i + j] == needle[j]) {
      j -= 1;
    }
    if (j == (-1)) return i;
    i += max(good_suff[j], bad_char[haystack[i + j]] - (t_len - 1 - j));
  }
  return -1;
}

}  // namespace base
