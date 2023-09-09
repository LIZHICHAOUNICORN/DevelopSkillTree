#include <string>
#include <array>
#include <locale>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/shortest-completing-word/

class Solution {
 private:
  void CalcWord(const string& word, array<int, 26>& cache) {
    VLOG(1) << word;
    for (int i = 0; i < word.size(); ++i) {
      if (std::isalpha(word[i])) {
        ++cache[tolower(word[i]) - 'a'];
        VLOG(1) << word[i] << ' '<< cache[tolower(word[i]) - 'a'];
      }
    }
  }

 public:
  string shortestCompletingWord(string licensePlate, vector<string>& words) {
    // 必须初始化，否则结果错误
    array<int, 26> ori {};
    CalcWord(licensePlate, ori);
    pair<int, int> ret = make_pair(0, 1001);
    for (int i = 0; i < words.size(); ++i) {
      array<int, 26> tmp {};
      CalcWord(words[i], tmp);
      bool found = true;
      for (int k = 0; k < 26; ++k) {
        if (tmp[k] < ori[k]) {
          found = false;
          break;
        }
      }
      if (found && words[i].length() < ret.second) {
        ret = make_pair(i, words[i].length());
      }
    }
    int offset = ret.first;
    return words[offset];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string licensePlate("1s3 PSt");
  vector<string> words({"step","steps","stripe","stepple"});
  Solution solu;
  string ret = solu.shortestCompletingWord(licensePlate, words);
  LOG(INFO) << ret;
  return 0;
}
