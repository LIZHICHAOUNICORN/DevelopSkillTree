#include <algorithm>
#include <deque>
#include <functional>
#include <queue>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/flatten-nested-list-iterator/

/* // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
 public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const {
    // pass
    return true
  }

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer
  // The result is undefined if this NestedInteger holds a nested list
  int getInteger() const { return 0; }

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list
  // The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const {
    return vector<NestedInteger>();
  }
};

class NestedIterator {
 private:
  int index_ = 0;
  vector<int> ret;

  void GetIntger(NestedInteger& nested, vector<int>& ret) {
    if (nested.isInteger()) {
      ret.push_back(nested.getInteger());
      return;
    }
    for (auto& it : nested.getList()) {
      GetIntger(it, ret);
    }
  }

 public:
  NestedIterator(vector<NestedInteger>& nestedList) : index_(0) {
    ret.clear();
    for (NestedInteger& it : nestedList) {
      GetIntger(it, ret);
    }
  }

  int next() {
    if (index_ < ret.size()) {
      index_ += 1;
      return ret[index_ - 1];
    }
    return -1;
  }

  bool hasNext() { return index_ < ret.size(); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  NestedIterator nest_it;

  return 0;
}
