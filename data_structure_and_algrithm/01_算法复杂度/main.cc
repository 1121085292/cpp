#include <iostream>

const int kcount = 10;
// for循环求和
int forLoop(int count){
    int sum = 0;
    for (size_t i = 1; i <= count; i++)
    {
        sum += i;
    }    
    return sum;
}

// 迭代求和
int recurtion(int count){
    if(count == 0){
        return 0;
    } else
    {
        return count + recurtion(count - 1);
    }
}

/* 斐波那契数列：递归 
给定一个第n个，求该数列的第n个数字*/
int fib(int count){
    if(count == 1 || count == 2){
        return count - 1;
    } else {
        return fib(count - 1) + fib(count - 2);
    }
}

int main(){
    int sum= 0, n = 0;
    // sum = forLoop(kcount);
    // sum = recurtion(kcount);
    n = fib(kcount);
    // std::cout << "1+2+3+...+100 = " << sum << std::endl;
    std::cout << " n = "<< kcount << ",fib n = " << n << std::endl;
    return 0;
}