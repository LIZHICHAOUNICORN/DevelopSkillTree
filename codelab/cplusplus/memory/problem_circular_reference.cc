#include <atomic>
#include <iostream>
#include <memory>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Child;
class Parent;

class Parent {
 private:
  // shared_ptr<Child> ChildPtr;
  weak_ptr<Child> ChildPtr;

 public:
  void setChild(shared_ptr<Child> child) { this->ChildPtr = child; }

  void doSomething() {
    // new shared_ptr
    if (this->ChildPtr.lock()) {
      LOG(INFO) << "Parent do something";
    }
  }

  ~Parent() {}
};

class Child {
 private:
  shared_ptr<Parent> ParentPtr;

 public:
  void setPartent(shared_ptr<Parent> parent) { this->ParentPtr = parent; }
  void doSomething() {
    if (this->ParentPtr.use_count()) {
    }
  }
  ~Child() {}
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  weak_ptr<Parent> wpp;
  weak_ptr<Child> wpc;
  {
    shared_ptr<Parent> p(new Parent);
    shared_ptr<Child> c(new Child);
    p->setChild(c);
    c->setPartent(p);
    wpp = p;
    wpc = c;
    cout << p.use_count() << endl;  // 2
    cout << c.use_count() << endl;  // 1
  }
  cout << wpp.use_count() << endl;  // 0
  cout << wpc.use_count() << endl;  // 0

  return 0;
}
