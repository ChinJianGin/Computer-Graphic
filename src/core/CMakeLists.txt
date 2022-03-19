cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(core)

add_library(core ./src/Window.cpp ./src/Input.cpp ./src/Timer.cpp ./src/OpenGLContext.cpp ./src/WindowInstance.cpp ./src/OrthoCamera.cpp)