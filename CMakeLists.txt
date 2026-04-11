cmake_minimum_required(VERSION 4.1)
project(SE350Project)

set(CMAKE_CXX_STANDARD 20)

#Just making this version required so I don't accidentally mix versions.
set(CCMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SE350Project src/main.cpp)
