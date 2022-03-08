#pragma once

#include<glad/glad.h>

class VBO
{
public:
    GLuint ID;

    template <typename T>
    VBO(T vertices, GLsizeiptr size);

    VBO(GLsizeiptr size);

    template <typename T>
    void LoadRealData(GLsizeiptr size_1, GLsizeiptr size_2,const T* data);
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

template <typename T>
inline void VBO::LoadRealData(GLsizeiptr size_1, GLsizeiptr size_2,const T* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, size_1, size_2, data);
}