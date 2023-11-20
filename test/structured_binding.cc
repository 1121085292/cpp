#include <iostream>
#include <tuple>
#include <string>

std::tuple<std::string, int> GreatePerson(){
  return { "dsa", 20 };
};

int main(){
  // std::tuple<std::string, int> person = GreatePerson();
  // std::string name = std::get<0>(person);
  // int age = std::get<1>(person);
  // c++17 结构化绑定
  auto[name, age] = GreatePerson();     //  等价上面代码
  std::cout << name << " :" << age << std::endl;
}