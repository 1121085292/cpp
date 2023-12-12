cmake_minimum_required(VERSION 3.15)

project(multi_sensor_mot)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cc)
add_executable(multi_sensor_mot ${SRC})

target_include_directories(multi_sensor_mot PRIVATE
            multi_sensor_mot/algorithm/kalman_filter
            multi_sensor_mot/interface)
