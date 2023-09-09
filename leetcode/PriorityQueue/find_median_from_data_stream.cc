#include <algorithm>
#include <queue>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/find-median-from-data-stream/

class MedianFinder {
 public:
  priority_queue<int, vector<int>, less<int>> queMin;
  priority_queue<int, vector<int>, greater<int>> queMax;

  MedianFinder() {}

  void addNum(int num) {
    if (queMin.empty() || num <= queMin.top()) {
      queMin.push(num);
      if (queMax.size() + 1 < queMin.size()) {
        queMax.push(queMin.top());
        queMin.pop();
      }
    } else {
      queMax.push(num);
      if (queMax.size() > queMin.size()) {
        queMin.push(queMax.top());
        queMax.pop();
      }
    }
  }

  double findMedian() {
    if (queMin.size() > queMax.size()) {
      return queMin.top();
    }
    return (queMin.top() + queMax.top()) / 2.0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  MedianFinder solu;
  solu.addNum(1);
  solu.addNum(2);
  double ret = solu.findMedian();
  LOG(INFO) << ret;

  return 0;
}
