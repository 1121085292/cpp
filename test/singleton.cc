#include <iostream>

class Singleton {
  public:

    static Singleton& get(){
      static Singleton singleton_;
      return singleton_;
    }
  private:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton& ) = delete;
    const Singleton &operator=(const Singleton& ) = delete;

};

int main(){
  Singleton::get();
}