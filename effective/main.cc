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

int main(){
  return 0;
}