// Author: zhichaoli
// Time: 2021年06月11日

#ifdef USE_GLOG

#include "glog/logging.h"
#include "gflags/gflags.h"

#else

#include <iostream>

#endif


class HasPtrMem {
 public:
  HasPtrMem(): count_(new int(0)) {}
  // Copy constructor with deep copy.
  HasPtrMem(const HasPtrMem& other):
    count_(new int(*other.count_)) {
  }
  ~HasPtrMem() {delete count_;}

  int * count_;
};


int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  HasPtrMem a;
  HasPtrMem b(a);
  std::cout << *a.count_ << std::endl;
  std::cout << *b.count_ << std::endl;

  return 0;
}
