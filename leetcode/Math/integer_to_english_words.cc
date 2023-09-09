#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/integer-to-english-words/submissions/

class Solution {
 public:
  vector<string> singles = {"",     "One", "Two",   "Three", "Four",
                            "Five", "Six", "Seven", "Eight", "Nine"};
  vector<string> teens = {"Ten",      "Eleven",  "Twelve",  "Thirteen",
                          "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                          "Eighteen", "Nineteen"};
  vector<string> tens = {"",      "Ten",   "Twenty",  "Thirty", "Forty",
                         "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
  vector<string> thousands = {"", "Thousand", "Million", "Billion"};

  string numberToWords(int num) {
    if (num == 0) {
      return "Zero";
    }
    string sb;
    for (int i = 3, unit = 1000000000; i >= 0; i--, unit /= 1000) {
      int curNum = num / unit;
      if (curNum != 0) {
        num -= curNum * unit;
        string curr;
        recursion(curr, curNum);
        curr = curr + thousands[i] + " ";
        sb = sb + curr;
      }
    }
    while (sb.back() == ' ') {
      sb.pop_back();
    }
    return sb;
  }

  void recursion(string& curr, int num) {
    if (num == 0) {
      return;
    } else if (num < 10) {
      curr = curr + singles[num] + " ";
    } else if (num < 20) {
      curr = curr + teens[num - 10] + " ";
    } else if (num < 100) {
      curr = curr + tens[num / 10] + " ";
      recursion(curr, num % 10);
    } else {
      curr = curr + singles[num / 100] + " Hundred ";
      recursion(curr, num % 100);
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string ret = solu.numberToWords(123);
  LOG(INFO) << ret;

  ret = solu.numberToWords(12345);
  LOG(INFO) << ret;

  ret = solu.numberToWords(1234567);
  LOG(INFO) << ret;

  return 0;
}
