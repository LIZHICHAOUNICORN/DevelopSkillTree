#include <cstring>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char* src = "Take the test";
  char dst[strlen(src)+1];
  strcpy(dst, src);
  dst[0] = 'M';
  printf("src = %s \t dst = %s\n", src, dst);

  char* buf = "Take the test over dst length";
  strncpy(dst, buf, sizeof buf);
  printf("buf = %s \t dst = %s\n", buf, dst);
  return 0;
}
