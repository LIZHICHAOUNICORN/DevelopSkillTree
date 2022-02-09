#ifndef NUM_GEN_H_
#define NUM_GEN_H_
#include "num_gen_observe.h"

#include <string>
#include <vector>

namespace practice {

class NumGen {
 public:
  explicit NumGen() = default;
  virtual ~NumGen() = default;

  void AddObserver(NumGenObServer* ob) {
    m_observer_list_.push_back(ob);
  }

  void NotifyAllObservers() {
    for (auto & ob : m_observer_list_) {
      ob->Update(this);
    }
  }

  virtual int GetNum() = 0;
  virtual void Exec() = 0;
  
 private:
  std::vector<NumGenObServer*> m_observer_list_;
};

}  // namespace practice


#endif // NUM_GEN_H_
