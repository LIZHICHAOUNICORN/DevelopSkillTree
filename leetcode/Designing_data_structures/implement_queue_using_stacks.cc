#include <algorithm>
#include <array>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::array;

class MyQueue {
  stack<int> in;
  stack<int> out;
  void reload() {
    while (in.size()) {
      out.push(in.top());
      in.pop();
    }
  }

 public:
  /** Initialize your data structure here. */
  MyQueue() {}

  /** Push element x to the back of queue. */
  void push(int x) { in.push(x); }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    if (out.size()) {
      int result = out.top();
      out.pop();
      return result;
    }
    reload();
    int result = out.top();
    out.pop();
    return result;
  }

  /** Get the front element. */
  int peek() {
    if (out.size()) return out.top();
    reload();
    return out.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() { return in.size() == 0 && out.size() == 0; }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
