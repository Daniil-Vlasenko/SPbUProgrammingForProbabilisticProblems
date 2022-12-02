cmake_minimum_required(VERSION 3.22)
project(Task2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task2 main.cpp
        /usr/include/boost/algorithm/string/split.hpp
        /usr/include/boost/algorithm/string/classification.hpp)
