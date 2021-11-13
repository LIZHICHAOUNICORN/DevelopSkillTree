/*
说明：程序是在 64 位编译器下测试的
*/
#include <iostream>

using namespace std;

class A {
 private:
  static int s_var;  // 不影响类的大小
  const int c_var;   // 4 字节
  int var;           // 8 字节 4 + 4 (int) = 8
  char var1;         // 12 字节 8 + 1 (char) + 3 (填充) = 12
 public:
  A(int temp) : c_var(temp) {}  // 不影响类的大小
  ~A() {}                       // 不影响类的大小
  virtual void f() { cout << "A::f" << endl; }

  virtual void g() { cout << "A::g" << endl; }

  virtual void h() {
    cout << "A::h" << endl;
  }  // 24 字节 12 + 4 (填充) + 8 (指向虚函数的指针) = 24
};

int main() {
  A ex1(4);
  A *p;
  cout << sizeof(p)
       << endl;  // 8 字节 注意：指针所占的空间和指针指向的数据类型无关
  cout << sizeof(ex1) << endl;  // 24 字节
  return 0;
}
