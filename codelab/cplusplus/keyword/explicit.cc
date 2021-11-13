#include <cstring>
#include <iostream>
using namespace std;

class A {
 public:
  int var;
  // explicit A(int tmp) { //
  // 用来声明类构造函数是显示调用的，而非隐式调用，可以阻止调用构造函数时进行隐式转换。
  // 只可用于修饰单参构造函数，因为无参构造函数和多参构造函数本身就是显示调用的，再加上
  // explicit 关键字也没有什么意义。
  A(int tmp) {
    var = tmp;
    cout << var << endl;
  }
};
int main() {
  A ex(100);
  A ex1 = 10;  // error: conversion from 'int' to non-scalar type 'A' requested
  return 0;
}
