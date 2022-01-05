#include "leetcode/Design/string.h"

#include <cstring>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

// 初始化列表
String::String() : str_(nullptr), str_size_(0) {
  VLOG(1) << "String constructor";
}

String::String(const char* other) {
  size_t len = strlen(other);
  str_ = new char[len + 1];
  strcpy(str_, other);
  VLOG(1) << "String constructor cstring";
}

String::String(const String& other) {
  str_size_ = other.size();
  str_ = new char[str_size_ + 1];
  strcpy(str_, other.str_);
  VLOG(1) << "String copy constructor";
}

String::String(String&& other) {
  str_size_ = other.size();
  str_ = other.str_;
  other.str_ = nullptr;
  VLOG(1) << "String move constructor";
}

String::~String() {
  if (str_ != nullptr) {
    delete[] str_;
  }
  str_ = nullptr;
  str_size_ = 0;
  VLOG(1) << "String destructor";
}
// Tradition
/*
String& String::operator=(const String& other) {
  // if (other == this) return *this;
  if (str_ != nullptr) {
    delete[] str_;
    str_size_ = 0;
  }
  str_size_ = other.size();
  str_ = new char[str_size_ + 1];
  strcpy(str_, other.str_);
  VLOG(1) << "String copy assignment";
  return *this;
}
*/
// Pass by value
String& String::operator=(String other) {
  swap(other);
  return *this;
}

String& String::operator=(String&& other) {
  if (str_ != nullptr) {
    delete[] str_;
    str_size_ = 0;
  }
  str_size_ = other.size();
  str_ = other.str_;
  other.str_ = nullptr;
  VLOG(1) << "String move assignment";
  return *this;
}

void String::swap(String& other) { std::swap(str_, other.str_); }

std::ostream& operator<<(std::ostream& os, const String& other) {
  os << other.c_str();
  VLOG(1) << "String friend << operator";
  return os;
}
}  // namespace base
