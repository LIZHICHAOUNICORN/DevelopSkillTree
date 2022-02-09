#ifndef DIGIT_OBSERVER_H_
#define DIGIT_OBSERVER_H_
#include <iostream>

#include "num_gen.h"
#include "num_gen_observe.h"


namespace practice {

class DigitObserver : public NumGenObServer {
 public:
  DigitObserver() = default;
  ~DigitObserver() = default;

  virtual void Update(NumGen* num_gen) override {
    std::cout << "DigitObserver" << num_gen->GetNum() << std::endl;
  }
};


}  // namespace practice
#endif  // DIGIT_OBSERVER_H_
