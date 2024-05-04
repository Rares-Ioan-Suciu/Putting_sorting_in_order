cmake_minimum_required(VERSION 3.27)
project(tester_sorting)

set(CMAKE_CXX_STANDARD 17)

add_executable(tester_sorting main.cpp
        menu.h
        menu.cpp)
