#ifndef OWN_STRING_
#define OWN_STRING_

#include <iostream>
#include <ostream>

namespace base {
class String {
 public:
  typedef int size_t;
  // constructor
  String();
  // Constructor
  String(const char* other);
  // copy constructor
  String(const String& other);
  // Move constructor
  String(String&& other);
  // Destructor
  ~String();

  size_t size() const { return str_size_; }
  bool empty() const { return str_size_ == 0; }
  const char* c_str() const { return str_; }

  // Tradition Copy assignment
  // String& operator=(const String& other);
  // use swap, not support cstring use copy assignment
  String& operator=(String other);
  // Move assignment
  String& operator=(String&& other);

  void swap(String& other);

  friend std::ostream& operator<<(std::ostream& os, const String& other);

 private:
  char* str_ = nullptr;
  size_t str_size_ = 0;
};
}  // namespace String
#endif  // OWN_STRING_
