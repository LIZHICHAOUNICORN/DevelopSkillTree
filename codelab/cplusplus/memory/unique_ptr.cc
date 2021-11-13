#include <iostream>
#include <memory>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
  // std::unique_ptr<int> uptr2 = uptr;  //不能賦值
  // std::unique_ptr<int> uptr2(uptr);  //不能拷貝
  std::unique_ptr<int> uptr2 = std::move(uptr);  //轉換所有權
  uptr2.release();                               //释放所有权

  return 0;
}
