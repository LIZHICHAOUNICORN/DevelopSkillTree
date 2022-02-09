
namespace util {
template <typename T>
class SingleTonWithArgs {
 public:
  template <typename ...Args>
  static T* Instance(Args&& ... args) {
    if (my_instance == nullptr) {
      my_instance = new T(std::forward<Args>(args)...);
    }
    return my_instance;
  }

  static T* GetInstance() {
    if (my_instance == nullptr) {
      std::throw std::logic_error("The instance not construct");
    }
    return my_instance;
  }

  static void DestoryInstance() {
    delete my_instance;
    my_instance = nullptr;
  }

 private:
  SingleTonWithArgs() = default;
  virtual ~SingleTonWithArgs = default;

  SingleTonWithArgs(const SingleTonWithArgs& other) = delete;
  SingleTonWithArgs(SingleTonWithArgs&& other) = delete;
  
  T & operator=(const SingleTonWithArgs& other) = delete;
  T & operator=(SingleTonWithArgs&& other) = delete;

  static T* my_instance;
};

SingleTonWithArgs::my_instance = nullptr;

}  // namespace util
