cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(2DShooting)

add_executable(${PROJECT_NAME} glad.c 2DMain.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw game core vertex shader)