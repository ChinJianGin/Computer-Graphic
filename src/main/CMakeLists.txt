cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(homework_2)

add_executable(${PROJECT_NAME} glad.c 3DMain.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw assimp fmt lightscene core vertex shader client light renderer physics) 