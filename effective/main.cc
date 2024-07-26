#include <iostream>
// 1.c++联邦：c++中c语言，面相对象（类的封装、继承和多态），c++中的模板，c++中的STL标准库
// 2.Prefer consts, enums, and inlines to #defines
/*  对于简单常量，首选const和enum
    类似函数的宏，优先选择内联函数  */
class GamePlayer {
  public:

  private:
    static const int num_turns_ = 5;  // 声明
    int scores[num_turns_];           // 使用
};

const int GamePlayer::num_turns_;

template<class T>
inline T CallWithMax(const T& a,const T& b){
  return f(a > b ? a : b);
}

// 3.Use const whenever possible
// 4.确保对象在使用前被初始化
// 5.了解c++默默编写并调用了哪些函数，类的默认构造，默认析构，拷贝构造等
// 6.不使用编译器自动生成的函数，需自己重新实现
// 7.为多态基类声明虚析构函数
class BaseTimer {
  public:
  enum class TimerType {
    Atomic, water 
  };
  public:
    BaseTimer(){
      std::cout << "BaseTimer constructor" << std::endl;
    }
    virtual ~BaseTimer(){
      std::cout << "BaseTimer destructor" << std::endl;
    }
  private:
};

class AtomicTimer : public BaseTimer{
  public:
    AtomicTimer(){
      std::cout << "AtomicTimer constructor" << std::endl;
    }
    ~AtomicTimer(){
      std::cout << "AtomicTimer destructor" << std::endl;
    }
  private:
};


class WaterTimer : public BaseTimer{
  public:
    WaterTimer(){
      std::cout << "WaterTimer constructor" << std::endl;
    }
    ~WaterTimer(){
      std::cout << "WaterTimer destructor" << std::endl;
    }
  private:
};

BaseTimer* getTimer(BaseTimer::TimerType type){
  switch (type)
  {
  case BaseTimer::TimerType::Atomic:
    return new AtomicTimer();
  case BaseTimer::TimerType::water:
    return new WaterTimer();
  default:
    return new BaseTimer();
  }
}

// 8.异常
// 9.构造和析构不调用虚函数
// 10.令 operator=返回一个指向*this(自己)的引用

int main(){
  // 7.为多态基类声明虚析构函数
  // BaseTimer* timer = getTimer(BaseTimer::TimerType::Atomic);
  // delete timer;

  return 0;
}