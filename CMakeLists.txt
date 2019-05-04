cmake_minimum_required(VERSION 3.13)
project(huntNkill)

set(CMAKE_CXX_STANDARD 14)

add_executable(huntNkill main.cpp hnkAllDemCells.h Generator.h Coordinator.h Coordinator.cpp Edge.h Edge.cpp)