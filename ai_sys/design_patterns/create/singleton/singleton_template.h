#ifndef SINGLE_TON_TEMPLATE_H_
#define SINGLE_TON_TEMPLATE_H_

#include <memory>

#include <gflags/gflags.h>
#include <glog/logging.h>

namespace util {
template <class T>
class SingleTon {
 public:
  static T& GetInstance() {
    static T ins;
    LOG(INFO) << "Get instance";
    return ins;
  }

 protected:
  SingleTon() = default;
  ~SingleTon() = default;

  SingleTon(const T& other) = delete;
  SingleTon(T&& other) = delete;

  T& operator=(const T& other) = delete;
  T& operator==(T&& other) = delete;
};
}

#endif  // SINGLE_TON_TEMPLATE_H_
