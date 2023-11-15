#include <iostream>

class Base {
  public:
    Base() { std::cout << "Base constructor" << std::endl; }
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
  public:
    Derived() { std::cout << "Derived constructor" << std::endl; }
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};


int main() {
  Base* base = new Base();
  delete base;
  std::cout << "================" << std::endl;
  // Derived* derived = new Derived();
  // delete derived;
  Base* poly = new Derived;
  delete poly;
}