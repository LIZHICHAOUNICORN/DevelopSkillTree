#include <algorithm>
#include <queue>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::queue;

class MyStack {
 public:
  queue<int> queue1;
  queue<int> queue2;

  /** Initialize your data structure here. */
  MyStack() {}

  /** Push element x onto stack. */
  void push(int x) {
    queue2.push(x);
    while (!queue1.empty()) {
      queue2.push(queue1.front());
      queue1.pop();
    }
    swap(queue1, queue2);
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop() {
    int r = queue1.front();
    queue1.pop();
    return r;
  }

  /** Get the top element. */
  int top() {
    int r = queue1.front();
    return r;
  }

  /** Returns whether the stack is empty. */
  bool empty() { return queue1.empty(); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
