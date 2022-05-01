#include <cstdarg>
#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// C-style "const char* fmt, ..." is also valid
void simple_printf(const char* fmt...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int i = va_arg(args, int);
      std::cout << i << '\n';
    } else if (*fmt == 'c') {
      // note automatic conversion to integral type
      int c = va_arg(args, int);
      std::cout << static_cast<char>(c) << '\n';
    } else if (*fmt == 'f') {
      double d = va_arg(args, double);
      std::cout << d << '\n';
    }
    ++fmt;
  }

  va_end(args);
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  simple_printf("dcff", 3, 'a', 1.999, 42.5);

  return 0;
}
