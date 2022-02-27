cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(shader)

add_library(shader ShaderClass.cpp)