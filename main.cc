#include <iostream>
#include <string>

class Entity {
  public:
   explicit Entity(const int age) : age_(age) {}

  private:
    int age_;
};

struct Vector2 {
    float x_, y_;

    Vector2(float x, float y)
        : x_(x), y_(y) {}
    Vector2 add(const Vector2& other) const {
        return Vector2(x_ + other.x_, y_ + other.y_);
    }
    Vector2 operator+(const Vector2& other) const {
        // return Vector2(x_ + other.x_, y_ + other.y_);
        return add(other);
    }
    Vector2 multiply(const Vector2& other) const {
        return Vector2(x_ * other.x_, y_ * other.y_);
    }
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x_ * other.x_, y_ * other.y_);
    }
};
    std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
        return stream << other.x_ << " " << other.y_;
    }

int main(){
    // Entity e(5);
    Vector2 speed(0.5f, 0.5f);
    Vector2 position(10.0f, 10.0f);
    Vector2 powerup(1.1f, 1.1f);
    // Vector2 result = position.add(speed.multiply(powerup));
    Vector2 result = position + speed * powerup;
    // std::cout << result.x_ << " " << result.y_ << std::endl;
    std::cout << result;
    return 0;
}
