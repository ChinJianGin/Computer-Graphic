cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(vertex)

add_library(vertex VAO.cpp EBO.cpp VBO.cpp)