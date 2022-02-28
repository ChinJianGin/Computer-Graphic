#pragma once

#include<glad/glad.h>
#include"../core/include/vector2.hpp"
#include"../core/include/vector3.hpp"

class VBO
{
public:
    GLuint ID;

    template <typename T>
    VBO(T vertices, GLsizeiptr size);

    VBO(GLsizeiptr size);

    void LoadRealData(GLsizeiptr size_1, GLsizeiptr size_2,const CustomVector::Vector3_float* data);
    void Bind();
    void UnBind();
    void Delete();

};

template <typename T>
inline VBO::VBO(T vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}