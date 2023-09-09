#include "ai_sys/design_patterns/create/singleton_template.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

class Model : public util::SingleTon<Model> {
  friend SingleTon<Model>;

 public:
  void Inference() { LOG(INFO) << "Inference"; }

 protected:
  Model() = default;
  ~Model() = default;
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Model& m = Model::GetInstance();
  m.Inference();

  return 0;
}
