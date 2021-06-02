#include <stack>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

class MinStack {
 private:
  stack<int> s1;
  stack<int> s2;
 public:
  void push(int x) {
	s1.push(x);
	if (s2.empty() || x <= getMin())  s2.push(x);	    
  }
  void pop() {
	if (s1.top() == getMin())  s2.pop();
	s1.pop();
  }
  int top() {
	return s1.top();
  }
  int getMin() {
	return s2.top();
  }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
