#ifndef RANDOM_NUM_GEN_H_
#define RANDOM_NUM_GEN_H_
#include "num_gen.h"

#include <iostream>
namespace practice { 
class RandomNumGen : public NumGen {
 public:
  RandomNumGen() {};
  ~RandomNumGen() {};

  virtual int GetNum() override {
    return num_;
  }
  virtual void Exec() override {
    for (int i = 0; i < 5; ++i) {
      num_ += i;
      std::cout << "RandomNumGen update" << GetNum() << std::endl;
      NotifyAllObservers();
    }
  }

 private:
  int num_ = 0;

};

}  // namespace practice

#endif  // RANDOM_NUM_GEN_H_
