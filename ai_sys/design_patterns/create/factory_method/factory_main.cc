#include "IDCardFactory.h"
#include "IFactory.h"
#include "IProduct.h"

int main(int argc, char* argv[]) {
  practice::IFactory * fac = new practice::IDCardFactory();
  practice::IProduct *p1 = fac->CreateProduct("p1");
  practice::IProduct *p2 = fac->CreateProduct("p2");

  p1->Use();
  p2->Use();

  return 0;
}
