cmake_minimum_required(VERSION 3.15)

project(multi_sensor_mot)

# add src
aux_source_directory(. sources)
aux_source_directory(interface sources)
aux_source_directory(algorithm/kalman_filter sources)

add_executable(multi_sensor_mot ${sources})

# add include
target_include_directories(multi_sensor_mot PRIVATE
            multi_sensor_mot/algorithm/kalman_filter
            multi_sensor_mot/interface)

set(CMAKE_BUILD_TYPE Debug)