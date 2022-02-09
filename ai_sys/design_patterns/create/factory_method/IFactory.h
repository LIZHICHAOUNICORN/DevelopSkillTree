#ifndef IFACTORY_H_
#define IFACTORY_H_
#include <string>


namespace practice {

class IProduct;

class IFactory {
 public:
  IFactory() = default;
  virtual ~IFactory() = default;

  virtual void RegistorProduct(IProduct* product) = 0;
  virtual IProduct *CreateProduct(const std::string& name) = 0;
  virtual IProduct * create(const std::string& name) {
    IProduct *product = CreateProduct(name);

    RegistorProduct(product);

    return product;
  }
};

}  // namespace practice

#endif  // IFACTORY_H_
