cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(lightscene)

add_library(lightscene ./src/Room.cpp)