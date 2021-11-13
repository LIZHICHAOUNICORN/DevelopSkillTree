#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

#include <cstring>
#include <iostream>

using namespace std;


int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  char arr[10] = "hello";
  cout << strlen(arr) << endl;  // 5
  cout << sizeof(arr) << endl;  // 10
  return 0;
}
