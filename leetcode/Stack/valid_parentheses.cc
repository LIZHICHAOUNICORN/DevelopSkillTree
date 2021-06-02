#include <stack>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

class Solution {
public:
bool isValid(string s) {
  if (s.empty()) return true;
  stack<char> cont;
  for (string::iterator it = s.begin(); it != s.end(); ++it) {
    if (*it == '{' || *it == '(' || *it == '[') {
      cont.push(*it);
      continue;
    } else if (*it == '}' || *it == ')' || *it == ']') {
      if (cont.empty()) return false;
      char left = cont.top();
      cont.pop();
      if (((*it == '}') && (left == '{')) ||
          ((*it == ')') && (left == '(')) ||
          ((*it == ']') && (left == '['))) {
        continue;
      }
      return false;
    }
  }
  if (cont.empty()) return true;
  return false;
  }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
