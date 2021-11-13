#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
  // simple usage
  char source[] = "once upon a midnight dreary...";
  char dest[4];
  std::memcpy(dest, source, sizeof dest);
  std::cout << "dest[4] = { ";
  for (char c : dest) std::cout << "'" << c << "', ";
  std::cout << "};\n";

  // object creation in destination buffer
  struct S {
    int x{42};
    void print() const { std::cout << "{" << x << "}\n"; }
  } s;
  alignas(S) char buf[sizeof(S)];
  S* ps = new (buf) S;  // placement new
  std::memcpy(ps, &s, sizeof s);
  ps->print();
}
