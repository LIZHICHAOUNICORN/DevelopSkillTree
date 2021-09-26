#include <algorithm>
#include <deque>
#include <limits>
#include <stack>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class MyQueue {
  stack<int> s1, s2;

 public:
  void push(int x) { s1.push(x); }

  int pop() {
    int element = peek();
    if (element == -1) return -1;
    s2.pop();
    return element;
  }

  int peek() {
    if (s2.empty() && s1.empty()) return -1;
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    return s2.top();
  }

  bool empty() { return s1.empty() && s2.empty(); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  MyQueue my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.peek();
  my_queue.pop();
  my_queue.empty();
  my_queue.push(1);
  my_queue.pop();
  return 0;
}
