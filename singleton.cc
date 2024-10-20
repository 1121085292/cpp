#include <iostream>

// class Singleton {
//  public:
//   Singleton(const Singleton& other) = delete;
//   Singleton& operator=(const Singleton& other) = delete;

//   static Singleton* GetInstance(const std::string& str) {
//     if (single_ == nullptr) {
//       single_ = new Singleton(str);
//     }

//     return single_;
//   }

//   std::string GetValue() { return value_; }

//  private:
//   Singleton(const std::string& str) : value_(str) {}
//   ~Singleton() = default;
//   static Singleton* single_;
//   std::string value_;
// };

// Singleton* Singleton::single_ = nullptr;

class Singleton {
 public:
  ~Singleton() = default;
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(const Singleton& s) = delete;

  static Singleton& GetInstance() {
    static Singleton singleton;
    return singleton;
  }

 private:
  Singleton() = default;
};

int main() {
  // Singleton* s1 = Singleton::GetInstance("foo");
  // std::cout << s1->GetValue() << std::endl;
  // Singleton* s2 = Singleton::GetInstance("haha");
  // std::cout << s2->GetValue() << std::endl;
  Singleton& s = Singleton::GetInstance();

  return 0;
}