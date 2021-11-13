#include <iostream>
using namespace std;

inline void A::fun(int var) { cout << var << endl; }

class A {
 public:
  int var;
  A(int tmp) { var = tmp; }
  // 类外定义成员函数，若想定义为内联函数，需用关键字声明
  // 当在类内声明函数，在类外定义函数时，如果想将该函数定义为内联函数，
  // 则可以在类内声明时不加 inline 关键字，而在类外定义函数时加上 inline 关键字。
  void fun();
};

int main() { return 0; }
