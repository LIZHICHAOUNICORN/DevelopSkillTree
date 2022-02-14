/*
说明：程序是在 64 位编译器下测试的
*/
#include <iostream>

using namespace std;
#pragma pack(8)


// 1. 结构体第一个成员的偏移量（offset）为0，以后每个成员相对于结构体首地址的
// offset 都是该成员大小与有效对齐值中较小那个的整数倍，
// 如有需要编译器会在成员之间加上填充字节。

// 2. 结构体的总大小为 有效对齐值
// 的整数倍，如有需要编译器会在最末一个成员之后加上填充字节。

struct A3 {
  char a;                // 1
  int b;                 // 4
  unsigned short c;      // 2
  long d;                // 8
  unsigned long long e;  // 8
  char f;                // 1
};
// A3大小为1+(3)+4+2+(6)+8+8+1+(7)=40，括号内是为了内存对齐加的padding大小

struct A4 {
  int b;
  char a;
  unsigned short c;
  long d;
  unsigned long long e;
  char f;
};
// A4大小为4+1+(1)+2+8+8+1+(7)=32

int main(int argc, char* argv[]) {
  short var;
  int var1;
  long var2;
  char var3;
  string s;

  A3 a3;
  cout << "struct A3 " << sizeof(a3) << endl;

  A4 a4;
  cout << "struct A4 " << sizeof(a4) << endl;

  return 0;
}
