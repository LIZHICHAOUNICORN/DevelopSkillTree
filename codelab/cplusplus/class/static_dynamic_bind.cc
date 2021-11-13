#include <cassert>
#include <iostream>

using namespace std;

class Base {
 public:
  virtual void fun() { cout << "Base::fun()" << endl; }
};
class Derive : public Base {
 public:
  void fun() { cout << "Derive::fun()"; }
};

/*
运行结果：
Derive::fun()
*/

int main(int argc, char *argv[]) {
  Base *p = new Derive();  // p 的静态类型是 Base*，动态类型是 Derive*
  p->fun();                // fun 是虚函数，运行阶段进行动态绑定
  return 0;
}
