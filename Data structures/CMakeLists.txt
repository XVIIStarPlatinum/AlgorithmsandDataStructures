cmake_minimum_required(VERSION 3.27)
project(Data_structures)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O2")

add_executable(Data_structures "Timus-VI(1628)/Problem1628.cpp")
