#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/smallest-k-lcci/

class Solution {
 public:
  vector<int> smallestK(vector<int>& arr, int k) {
    vector<int> vec(k, 0);
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < k; ++i) {
      vec[i] = arr[i];
    }
    return vec;
  }
};

class Solution1 {
 public:
  vector<int> smallestK(vector<int>& arr, int k) {
    vector<int> vec(k, 0);
    if (k == 0) {  // 排除 0 的情况
      return vec;
    }
    priority_queue<int> Q;
    for (int i = 0; i < k; ++i) {
      Q.push(arr[i]);
    }
    for (int i = k; i < (int)arr.size(); ++i) {
      if (Q.top() > arr[i]) {
        Q.pop();
        Q.push(arr[i]);
      }
    }
    for (int i = 0; i < k; ++i) {
      vec[i] = Q.top();
      Q.pop();
    }
    return vec;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
