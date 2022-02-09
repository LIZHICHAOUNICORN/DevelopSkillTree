#ifndef GRAPH_OBSERVER_H_
#define GRAPH_OBSERVER_H_
#include <iostream>

#include "num_gen.h"
#include "num_gen_observe.h"


namespace practice {

class GraphObserver : public NumGenObServer {
 public:
  GraphObserver() = default;
  ~GraphObserver() = default;

  void Update(NumGen* num_gen) override {
    std::cout << "GraphObserver" << num_gen->GetNum() << std::endl;
  }
};


}  // namespace practice
#endif  // GRAPH_OBSERVER_H_
