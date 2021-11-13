#include <iostream>

using namespace std;

class A {
 public:
  void funA() { cout << "class A" << endl; }
};

struct B : A {  // 由于 B 是 struct，A 的默认继承级别为 public
 public:
  void funB() { cout << "class B" << endl; }
};

class C : B {  // 由于 C 是 class，B 的默认继承级别为 private，所以无法访问基类
               // B 中的 printB 函数
};

int main() {
  A ex1;
  ex1.funA();  // class A

  B ex2;
  ex2.funA();  // class A
  ex2.funB();  // class B

  C ex3;
  // ex3.funA();
  // ex3.funB();  // error: 'B' is not an accessible base of 'C'.
  return 0;
}
