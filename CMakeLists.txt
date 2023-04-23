cmake_minimum_required(VERSION 3.25)
project(task_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_2 src/main.cpp src/brute_force.h src/utils.h src/utils.cpp)

find_package(OpenSSL REQUIRED)

target_link_libraries(task_2 OpenSSL::SSL)

#target_link_libraries(tests GTest::gtest GTest::gtest_main)