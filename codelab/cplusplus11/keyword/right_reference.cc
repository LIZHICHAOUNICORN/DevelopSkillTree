#include <algorithm>
#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  int var = 42;
  int &l_var = var;
  // int &&r_var = var;  // error: cannot bind rvalue reference of type 'int&&' to
                         // lvalue of type 'int' 错误：不能将右值引用绑定到左值上

  int &&r_var2 = var + 40;  // 正确：将 r_var2 绑定到求和结果上
  LOG(INFO) << r_var2;

  return 0;
}
