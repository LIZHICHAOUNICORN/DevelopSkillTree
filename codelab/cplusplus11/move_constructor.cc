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
  HasPtrMem(): count_(new int(0)) {
    std::cout << "Counstrctor " << ++n_cstr << std::endl;
  }
  // Copy constructor with deep copy.
  HasPtrMem(const HasPtrMem& other):
    count_(new int(*other.count_)) {
    std::cout << "Copy Constructor " << ++n_cptr << std::endl;
  }
  ~HasPtrMem() {
    delete count_;
    std::cout << "Destructor " << ++n_dstr << std::endl;
  }

  static int n_cstr;
  static int n_dstr;
  static int n_cptr;
  int * count_;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_dstr = 0;

HasPtrMem GetTemp() {
  return HasPtrMem();
}

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  //
  HasPtrMem a = GetTemp();

  return 0;
}
