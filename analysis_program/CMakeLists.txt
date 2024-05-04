cmake_minimum_required(VERSION 3.27)
project(analysis_program)

set(CMAKE_CXX_STANDARD 17)

add_executable(analysis_program main.cpp
        data_generator.h
        data_generator.cpp
        sorting.h
        sorting.cpp
        timsort.cpp
        timsort.h
        introsort.cpp
        introsort.h
        "O(n^2).h"
        "O(n^2).cpp"
        "O(nlogn).cpp"
        "O(nlogn).h"
        Non-comparison.cpp
        Non-comparison.h
)
