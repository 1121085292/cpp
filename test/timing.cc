#include <iostream>
#include <chrono>
#include <thread>

struct Timer {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> duration;
    Timer(){
        start = std::chrono::high_resolution_clock::now();

    }

    ~Timer(){
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << "Time took :" << ms << "ms" << std::endl;
        // std::cout << "time took :" << duration.count() << "s" << std::endl;
    }
};

void function(){
    Timer timer;
    for (size_t i = 0; i < 100; i++)
    {
        // std::cout << "hello" << std::endl;  //  5.256ms
        std::cout << "hello\n";  //  5.256ms
    }
    
}

int main() {
    function();

    return 0;
}