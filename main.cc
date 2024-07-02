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

现在有个车辆模型，车身坐标系x向前，y向左，z向上，安装了12个超声波雷达，已知雷达在车身坐标系下的安装位置和与X轴夹角，同时在自车周围12.5×12×1.5m范围内生成了0.05×0.05×0.2尺寸的3D栅格，以左下角为起点，ijk排序，当探头在探测到目标后会返回一个回波，包含距离和幅值信息，我怎么根据这个回波找到此时所占据的栅格id。可以将回波类比成一个以距离D为半径，安装位置为球心的球面，但是有探测范围限制，方向是沿安装方向，只有部分球面，先讲原理
