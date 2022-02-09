#include <memory>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

class SingleTon {
 public:
  inline static SingleTon& Instance() {
    // cpp 编译器保证 对于inline 函数的static local
    // 变量，只有一个实例，同时保证线程安全。
    static SingleTon instance;
    LOG(INFO) << "Get instance";
    return instance;
  }

  void Init(std::shared_ptr<int> ptr) {
    ptr_ = ptr;
  }
  std::shared_ptr<int> GetPtr() {
    return ptr_;
  }

 private:
  SingleTon() = default;
  ~SingleTon() = default;

  SingleTon(const SingleTon& other) = delete;
  SingleTon(SingleTon&& other) = delete;

  SingleTon& operator=(const SingleTon& other) = delete;
  SingleTon& operator==(SingleTon&& other) = delete;

  std::shared_ptr<int> ptr_;
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  SingleTon& instance = SingleTon::Instance();

  return 0;
}
