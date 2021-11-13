#include <iostream>

using namespace std;

class A {
 public:
  int var1, var2;
  A() {
    var1 = 10;
    var2 = 20;
  }

  // 不能在 const
  // 修饰的成员函数中修改成员变量的值，除非该成员变量用
  // mutable 修饰
  void fun() const {
    // {
    //   var1 = 100;  // error: assignment of member 'A::var1' in read-only
    //   object
    // }
    return;
  }
};

int main(int argc, char *argv[]) {
  A ex1;

  return 0;
}
