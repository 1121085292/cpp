#include <iostream>

struct Vector2 {
  float x, y;
};

struct Vector4 {
  union {
    struct {
      float x, y, z, w;
    };
    struct {
      Vector2 a, b;
    };
  };
};

void printVector(const Vector2& v){
  std::cout << v.x << ", " << v.y << std::endl;
}

int main(){
  Vector4 vec = { 1.0f, 2.0f, 3.0f, 4.0f };
  printVector(vec.a);
  printVector(vec.b);
  vec.z = 500.0f;
  std::cout << "==================" << std::endl;
  printVector(vec.a);
  printVector(vec.b);
}