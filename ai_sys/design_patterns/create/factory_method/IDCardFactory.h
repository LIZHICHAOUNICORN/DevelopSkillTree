#ifndef IDCARD_FACTORY_H_
#define IDCARD_FACTORY_H_

#include <string>
#include <vector>

#include "IFactory.h"
#include "IDCard.h"

namespace practice {

class IDCardFactory : public IFactory {
 public:
  IDCardFactory() = default;
  ~IDCardFactory() {
    for (int i = 0; i < m_product_.size(); ++i) {
      delete m_product_[i];
      m_product_[i] == nullptr;
    }
  }

  IProduct* CreateProduct(const std::string& name) override {
    return new IDCard(name);
  }

  void RegistorProduct(IProduct* pro) override {
    m_product_.push_back(pro);
  }

 private:
  std::vector<IProduct *> m_product_;

};


}  // namesapce practice

#endif  // IDCARD_FACTORY_H_
