cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(physics)

add_library(physics BoundingVolume.cpp Transform.cpp)