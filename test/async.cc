#include <iostream>
#include <mutex>
#include <future>
#include <vector>

#include "meta.h"

size_t func(size_t val){
  int tmp = val;
  for(int i = 1; i <= tmp; ++i){
    val *= i;
  }
  // std::cout << tmp << "! = " << val << std::endl;
  return val;
}

int main(){
  {  
    Timer timer;
    size_t arr[] = { 10, 15, 20, 22, 24 };
    std::vector<std::future<size_t>> futures; 
    std::mutex mtx;

#define ASYNC 0
#if ASYNC
    for(int i = 0; i < 3; i++){
      std::lock_guard<std::mutex> lock(mtx);
      futures.push_back(std::async(std::launch::async, func, arr[i]));
    }
#else 
    for(int i = 0; i < 3; i++){
      func(arr[i]);
    }
#endif
  }
}