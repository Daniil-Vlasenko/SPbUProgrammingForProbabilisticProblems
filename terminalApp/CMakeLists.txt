cmake_minimum_required(VERSION 3.22)
project(terminalApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(terminalApp main.cpp mathLibrary.cpp mathLibrary.h)
