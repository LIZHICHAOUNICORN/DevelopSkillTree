#include <vector>
#include <array>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::array;

// Mysolution
class MinStack {
private:
    stack<int> data;
    stack<int> min_stack;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int val) {
        data.push(val);
        // It has to be `>=` simbal, because maybe have same min. the case below:
        // ["MinStack","push","push","push","getMin","pop","getMin"]
		// [[],[0],[1],[0],[],[],[]]
        if (min_stack.empty() || min_stack.top() >= val) {
            min_stack.push(val);
        }
    }
    
    void pop() {
        int value = data.top();
        data.pop();
        if (min_stack.size() > 0 && value == min_stack.top()) {
            min_stack.pop();
        }
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

// Official
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
