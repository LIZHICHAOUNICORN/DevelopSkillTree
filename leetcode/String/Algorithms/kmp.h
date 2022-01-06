#ifndef ALGORITHM_STRING_KMP_
#define ALGORITHM_STRING_KMP_

#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

// 暴力
class KMP {
 private:
  std::vector<int> next_;
  void BuildNext(const std::string& pattern);
  void FastBuildNext(const std::string& pattern);

 public:
  void Search(const std::string& src, const std::string& pattern,
              std::vector<int>& result);
};

}  // namespace base
#endif  // STRING_KMP_
