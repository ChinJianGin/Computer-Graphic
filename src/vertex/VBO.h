#pragma once

#include<glad/glad.h>
#include"../core/include/vector2.hpp"
#include"../core/include/vector3.hpp"

class VBO
{
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);
    VBO(CustomVector::Vector2_float* vertices, GLsizeiptr size);
    VBO(CustomVector::Vector3_float* vertices, GLsizeiptr size);

    void Bind();
    void UnBind();
    void Delete();

};