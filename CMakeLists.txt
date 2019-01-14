cmake_minimum_required(VERSION 3.13)
project(Day4_part1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Day4_part1 main.cpp Guards.h Guards.cpp)
target_compile_options(Day4_part1 PRIVATE -g3)