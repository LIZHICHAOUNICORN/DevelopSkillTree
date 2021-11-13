#include <iostream>
using namespace std;

int main() {
  // 局部变量声明
  const int i = 2;
  switch (i) {
    case 1:
      std::cout << "1";
    case 2:
      std::cout << "2";  // execution starts at this case label
    case 3:
      std::cout << "3";
      [[fallthrough]];  // C++17 attribute to silent
    case 4:             // the warning on fall through
    case 5:
      std::cout << "45";
      break;  // execution of subsequent statements is terminated
    case 6:
      std::cout << "6";
  }

  std::cout << '\n';

  return 0;
}
