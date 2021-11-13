#include <iostream>

using namespace std;

class Empty {};

int add(int a, int b) { return a + b; }

class A {
 public:
  int var1, var2;
  int add() { return var1 + var2; }
};

int main() {
  int *p = nullptr;
  cout << "int 指针大小: " << sizeof(p) << endl;  // 8

  char *p1 = nullptr;
  cout << "char 指针大小:" << sizeof(p1) << endl;  // 8

  // 对象指针
  Empty *ep = new Empty();
  cout << "空对象指针大小:" << sizeof(ep) << endl;  // 8
  delete ep;

  // 指针指向的对象不能通过这个指针来修改，也就是说常量指针可以被赋值为变量的地址，
  // 之所以叫做常量指针，是限制了通过这个指针修改变量的值。
  // 虽然常量指针指向的对象不能变化，可是因为常量指针本身是一个变量，因此，可以被重新赋值。
  // const int * p;
  // 注意 1：指针常量的值是指针，这个值因为是常量，所以指针本身不能改变。
  // 注意 2：指针的内容可以改变。
  // int const * p;
  // 常量指针
  const int c_var = 10;
  const int *const_p = &c_var;
  cout << "常量指针的内容:" << *const_p << endl;

  // 函数指针
  int (*fun_p)(int, int);
  fun_p = add;
  cout << "函数指针的结果:" << fun_p(1, 6) << endl;

  // 对象指针
  // 指向对象成员的指针，包括指向对象成员函数的指针和指向对象成员变量的指针。
  // 特别注意：定义指向成员函数的指针时，要标明指针所属的类。
  A ex;
  ex.var1 = 3;
  ex.var2 = 4;
  int *p_mem = &ex.var1;  // 指向对象成员变量的指针
  cout << "成员变量的结果:" << *p_mem << endl;

  int (A::*mem_fun_p)();
  mem_fun_p = &A::add;  // 指向对象成员函数的指针 fun_p
  cout << "成员函数结果：" << (ex.*mem_fun_p)() << endl;

  return 0;
}
