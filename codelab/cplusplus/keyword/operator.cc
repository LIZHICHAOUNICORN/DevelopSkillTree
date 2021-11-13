#include <cstring>
#include <iostream>
using namespace std;

struct A {
  char c;
  int val;
  A(char c_tmp, int tmp) : c(c_tmp), val(tmp) {}

  friend bool operator==(const A &tmp1, const A &tmp2);  //  友元运算符重载函数
};

bool operator==(const A &tmp1, const A &tmp2) {
  return (tmp1.c == tmp2.c && tmp1.val == tmp2.val);
}

int main() {
  A ex1('a', 90), ex2('b', 80);
  if (ex1 == ex2)
    cout << "ex1 == ex2" << endl;
  else
    cout << "ex1 != ex2" << endl;  // 输出
  return 0;
}
