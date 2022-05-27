
cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(light)

add_library(light ./DirectionLight.cpp ./PointLight.cpp ./SpotLight.cpp)