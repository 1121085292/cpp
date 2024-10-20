#include <iostream>
#include <memory>

#define simple_factory 0
#define factory_method 1

#if simple_factory

enum class Type { A, B };
// 产品
class Product {
 public:
  virtual ~Product() { std::cout << " ~Product." << std::endl; };

  virtual void Print() const { std::cout << "Product." << std::endl; };
};

class ConcreteProductA : public Product {
 public:
  ~ConcreteProductA() { std::cout << " ~ConcreteProductA." << std::endl; }
  void Print() const override { std::cout << "ConcreteProductA." << std::endl; }
};

class ConcreteProductB : public Product {
 public:
  ~ConcreteProductB() { std::cout << " ~ConcreteProductB." << std::endl; }

  void Print() const override { std::cout << "ConcreteProductB." << std::endl; }
};
// 工厂
class Factory {
 public:
  Product* Create(const Type& type) {
    switch (type) {
      case Type::A:
        return new ConcreteProductA;

      default:
        return new ConcreteProductB;
    }
  };
};
#endif

#if factory_method
// 产品
class Product {
 public:
  virtual ~Product() { std::cout << " ~Product." << std::endl; };

  virtual void Print() const { std::cout << "Product." << std::endl; };
};

class ConcreteProductA : public Product {
 public:
  ~ConcreteProductA() { std::cout << " ~ConcreteProductA." << std::endl; }
  void Print() const override { std::cout << "ConcreteProductA." << std::endl; }
};

class ConcreteProductB : public Product {
 public:
  ~ConcreteProductB() { std::cout << " ~ConcreteProductB." << std::endl; }

  void Print() const override { std::cout << "ConcreteProductB." << std::endl; }
};

// 工厂
class Factory {
 public:
  virtual std::unique_ptr<Factory> Create() = 0;
};

class ConcreteFactoryA : Factory {
 public:
  std::unique_ptr<Factory> Create() {
    return std::unique_ptr<Factory>(new ConcreteFactoryA);
  }
};

class ConcreteFactoryB : Factory {
 public:
  std::unique_ptr<Factory> Create() {
    return std::unique_ptr<Factory>(new ConcreteFactoryB);
  }
};
#endif

int main() {
#if simple_factory
  Factory* f = new Factory();
  auto p = f->Create(Type::B);
  p->Print();
  delete f;
  delete p;
#endif

#if factory_method
  Factory* f = new Factory();

#endif
}