#include <iostream>

using namespace std;

typedef union {
  char c[10];
  char cc1;  // char 1 字节，按该类型的倍数分配大小
} u11;

typedef union {
  char c[10];
  int i;  // int 4 字节，按该类型的倍数分配大小
} u22;

typedef union {
  char c[10];
  double d;  // double 8 字节，按该类型的倍数分配大小
} u33;

typedef struct s1 {
  char c;    // 1 字节
  double d;  // 1（char）+ 7（内存对齐）+ 8（double）= 16 字节
} s11;

typedef struct s2 {
  char c;    // 1 字节
  char cc;   // 1（char）+ 1（char）= 2 字节
  double d;  // 2 + 6（内存对齐）+ 8（double）= 16 字节
} s22;

typedef struct s3 {
  char c;    // 1 字节
  double d;  // 1（char）+ 7（内存对齐）+ 8（double）= 16 字节
  char cc;   // 16 + 1（char）+ 7（内存对齐）= 24 字节
} s33;

int main() {
  cout << sizeof(u11) << endl;  // 10
  cout << sizeof(u22) << endl;  // 12
  cout << sizeof(u33) << endl;  // 16
  cout << sizeof(s11) << endl;  // 16
  cout << sizeof(s22) << endl;  // 16
  cout << sizeof(s33) << endl;  // 24

  cout << sizeof(int) << endl;     // 4
  cout << sizeof(double) << endl;  // 8
  return 0;
}
