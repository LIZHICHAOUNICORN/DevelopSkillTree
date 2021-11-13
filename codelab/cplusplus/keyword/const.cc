#include <cstring>
#include <iostream>
using namespace std;

class A {
 public:
  int var;
  A(int tmp) : var(tmp) {}
  void c_fun(int tmp) const  // const 成员函数
  {
    // var = tmp; // error: assignment of member 'A::var' in read-only object.
    // 在 const 成员函数中，不能修改任何类成员变量。
    // fun(tmp); // error: passing 'const A' as 'this' argument discards
    // qualifiers. const 成员函数不能调用非 const 成员函数，因为非 const
    // 成员函数可能会修改成员变量。
  }

  void fun(int tmp) { var = tmp; }
};

#include <iostream>
#define INTPTR1 int*
typedef int* INTPTR2;

using namespace std;

int main() {
  INTPTR1 p1, p2;  // p1: int *; p2: int
  INTPTR2 p3, p4;  // p3: int *; p4: int *

  int var = 1;
  const INTPTR1 p5 = &var;  // 相当于 const int * p5; 常量指针，即不可以通过 p5
  // 去修改 p5 指向的内容，但是 p5 可以指向其他内容。
  const INTPTR2 p6 =
      &var;  // 相当于 int * const p6; 指针常量，不可使 p6 再指向其他内容。

  return 0;
}
