cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64")

add_executable(MainProgram main.cpp functions.cpp)

find_package(GTest REQUIRED)

include_directories(Tests ${GTEST_INCLUDE_DIRS})
link_directories(Tests ${GTEST_LIBRARY_DIRS})

add_executable(Tests tests.cpp functions.cpp)

target_link_libraries(Tests GTest::gtest GTest::gmock)
