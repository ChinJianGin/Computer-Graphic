cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(renderer)

add_library(renderer Triangle.cpp Quad.cpp Line.cpp Circle.cpp Shape.cpp OpenGLRenderCommand.cpp Render2D.cpp RenderCommand.cpp Renderer.cpp RenderInterface.cpp Texture.cpp OpenGLTexture.cpp Skybox.cpp Pyramid.cpp LightBox.cpp Box.cpp Plane.cpp 3DModel.cpp ./ModelLoad/Mesh.cpp ./ModelLoad/Model.cpp)