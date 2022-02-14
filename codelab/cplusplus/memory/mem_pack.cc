/*
说明：程序是在 64 位编译器下测试的
*/
#include <iostream>

using namespace std;
#pragma pack(8)

struct A {
  short var;  // 2 字节
  int var1;   // 8 字节 （内存对齐原则：填充 2 个字节） 2 (short) + 2 (填充) + 4
              // (int)= 8
  long var2;  // 16 字节 8 + 8 (long) = 16
  char var3;  // 16 字节 （内存对齐原则：填充 3 个字节）16 + 1 (char) + 3 (填充)
              // = 20
  string s;   // 48 字节 20 + 8 (string) = 28
};

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
  A ex1;
  cout << "short var " << sizeof(var) << endl;  // 2 short
  cout << "int var " << sizeof(var1) << endl;   // 4 int
  cout << "long var " << sizeof(var2) << endl;  // 8 long
  cout << "char var " << sizeof(var3) << endl;  // 1 char
  cout << "string var " << sizeof(s) << endl;   // 8 string
  cout << "struct A " << sizeof(ex1) << endl;   // 32 struct

  A3 a3;
  cout << "struct A3 " << sizeof(a3) << endl;

  A4 a4;
  cout << "struct A4 " << sizeof(a4) << endl;

  return 0;
}
