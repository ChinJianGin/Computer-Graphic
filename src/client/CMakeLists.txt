cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(client)

add_library(client ./src/Creator.cpp ./src/Button.cpp ./src/Interface.cpp)