#include <iostream>

int randomAccess(int* arr, int size){
    int random = rand() % size;
    return arr[random];
}

// 在不扩容的前提下插入数据
void insert(int* arr, int size, int num, int index){
    for (size_t i = size - 1; i > index; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[index] = num;
}

//删除数组中index位置元素
void remove(int* arr, int size, int index){
    for (size_t i = index; i < size - 1; i++)
    {
        arr[i] = arr[i+1];
    }
} 

// 扩容数组
int* extend(int* arr, int size, int enlarge){
    // 初始化一个扩展长度后的数组
    int* nums = new int[ size + enlarge ];
    // 将原数组中的所有元素复制到新数组
    for(int i = 0; i < size; i++){
        nums[i] = arr[i];
    }
    // 释放原堆上的数组
    // delete[] nums;
    // 返回扩展后的新数组
    return nums;
}

int main(){
    //  存储在栈上
    int arr[5] = {0, 1, 2, 3, 4};
    // 存储在堆上（需要手动释放空间）
    // int* arr = new int[5] {0, 1, 2, 3, 4};
    // delete[] arr;
    int a = 0;
    // a = randomAccess(arr, 5);
    // insert(arr, 5, 10, 3);
    remove(arr, 5, 3);
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    // std::cout << a << std::endl;
    return 0;
}