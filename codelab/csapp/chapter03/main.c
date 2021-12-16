#include <stdio.h>

void multstore(long x, long y, long* dst);

int main() {
  long d;
  multstore(2,3,&d);
  printf("2*3 -> %ld\n", d);
  return 0;
}
