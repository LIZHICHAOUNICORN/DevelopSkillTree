#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    int m = s.size();
    int n = p.size();
    if (m < n) return result;
    vector<int> win(26, 0);  //定义窗口字母统计数组
    vector<int> st(26, 0);
    for (int i = 0; i < n; i++) st[p[i] - 'a']++;
    int slow = 0;
    for (int fast = 0; fast < m; fast++) {
      win[s[fast] - 'a']++;
      if (fast >= n) {
        win[s[slow] - 'a']--;
        slow++;
      }  //达到p的大小后，每次fast和slow同时移动
      if (st == win) {
        result.push_back(slow);
      }
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution  solu;
  vector<int> ret = solu.findAnagrams("cbaebabacd", "abc");
  for (const int & r : ret) {
    LOG(INFO) << r;
  }

  return 0;
}
