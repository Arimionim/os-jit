cmake_minimum_required(VERSION 2.5)
project(OS_jit)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(OS_jit main.cpp)