#ifndef IPRODUCT_H_
#define IPRODUCT_H_
namespace practice {
class IProduct {
 public:
  IProduct() = default;
  virtual ~IProduct() = default;

  virtual void Use() = 0;
};

}  // namespace practice

#endif  // IPRODUCT_H_
