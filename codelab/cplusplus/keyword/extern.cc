#include <iostream>
#include <cstring>
using namespace std;

extern "C"{
    int strcmp(const char*, const char*);
}

int main() {
  char src[] = "hello";
  char tgt[] = "world";
  int ret = strcmp(src, tgt);
  cout << ret << endl;
  return 0;
}
