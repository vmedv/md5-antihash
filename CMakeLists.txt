cmake_minimum_required(VERSION 3.25)
project(task_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_2 src/main.cpp src/brute_force.h src/utils.h src/utils.cpp)

SET(CMAKE_BUILD_TYPE Release)

find_package(OpenSSL REQUIRED)

target_link_libraries(task_2 OpenSSL::SSL)

#add_custom_target(tests tests.cpp)
add_executable(tests tests.cpp src/brute_force.h src/utils.cpp)
add_dependencies(tests task_2)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(GTest QUIET)
if (NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            GTest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(GTest)
endif ()

target_link_libraries(tests GTest::gtest GTest::gtest_main)