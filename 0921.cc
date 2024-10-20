#include <iostream>
#include <numeric>  // std::iota
#include <random>   // std::random_device, std::mt19937, std::shuffle
#include <vector>

int main() {
  std::vector<int> v(10);

  // 初始化向量 v 为 1 到 10 的连续整数
  std::iota(v.begin(), v.end(), 1);

  std::random_device rd;
  std::mt19937 gen(rd());

  // 打乱向量中的元素
  std::shuffle(v.begin(), v.end(), gen);

  // 输出打乱后的向量
  for (const auto& i : v) {
    std::cout << i << " ";
  }

  return 0;
}
