#ifndef NUM_GEN_OBSERVE_H_
#define NUM_GEN_OBSERVE_H_
namespace practice {
class NumGen;

class NumGenObServer {
 public:
  NumGenObServer() = default;
  virtual ~NumGenObServer() = default;

  virtual void Update(NumGen* num_gen) = 0;
};

}  // namespace practice
#endif  // NUM_GEN_OBSERVE_H_
