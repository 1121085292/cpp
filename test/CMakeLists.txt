cmake_minimum_required(VERSION 3.15)

project(test)

# add_executable(test timing.cc)
# add_executable(test union.cc)
# add_executable(test virtual_destructor.cc)
# add_executable(test dynamic_cast.cc)
# add_executable(test timer.cc)
# add_executable(test structured_binding.cc)
add_executable(test optional.cc)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

# 将源代码目录添加到可执行文件的包含目录中
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})