cmake_minimum_required(VERSION 3.15)

project(multi_sensor_mot)

# add src
aux_source_directory(. sources)
aux_source_directory(${PROJECT_SOURCE_DIR}/algorithm/kalman_filter sources)
aux_source_directory(${PROJECT_SOURCE_DIR}/measurement sources)
aux_source_directory(${PROJECT_SOURCE_DIR}/fusion_system/motion_fusion sources)

add_executable(multi_sensor_mot ${sources})

# add include
target_include_directories(multi_sensor_mot PUBLIC ${PROJECT_SOURCE_DIR})


set(CMAKE_BUILD_TYPE Debug)