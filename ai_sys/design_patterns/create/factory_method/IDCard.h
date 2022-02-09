#ifndef IDCARD_H_
#define IDCARD_H_

#include "IProduct.h"

#include <string>
#include <iostream>

namespace practice {

class IDCard : public IProduct {
 public:
  IDCard(const std::string& name) : name_(name) {}
  ~IDCard() = default;

  void Use() override {
    std::cout << name_ << std::endl;
  }


 private:
  std::string name_;
};

}  // namespace practice

#endif  // IDCARD_H_
