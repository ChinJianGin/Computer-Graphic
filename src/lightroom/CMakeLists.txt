cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(lightroomobj)

add_library(lightroomobj ModelObject.cpp)