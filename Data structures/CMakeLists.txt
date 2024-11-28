cmake_minimum_required(VERSION 3.27.1)
project(Data_structures)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O2")

add_executable(Data_structures "treap.cpp")
