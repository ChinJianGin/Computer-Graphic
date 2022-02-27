cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(Example1)

add_executable(${PROJECT_NAME} glad.c Example1.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw vertex shader core)