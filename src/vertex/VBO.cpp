#include"VBO.h"

// VBO::VBO(GLfloat* vertices, GLsizeiptr size)
// {
//     glGenBuffers(1, &ID);
//     glBindBuffer(GL_ARRAY_BUFFER, ID);
//     glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
// }

// VBO::VBO(CustomVector::Vector2_float* vertices, GLsizeiptr size)
// {
//     glGenBuffers(1, &ID);
//     glBindBuffer(GL_ARRAY_BUFFER, ID);
//     glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
// }

// VBO::VBO(CustomVector::Vector3_float* vertices, GLsizeiptr size)
// {
//     glGenBuffers(1, &ID);
//     glBindBuffer(GL_ARRAY_BUFFER, ID);
//     glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
// }

VBO::VBO(GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}

void VBO::LoadRealData(GLsizeiptr size_1, GLsizeiptr size_2,const CustomVector::Vector3_float* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, size_1, size_2, data);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}