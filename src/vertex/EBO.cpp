#include"EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size): m_size(size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

CustomSpace::Ref<EBO> EBO::Create(GLuint* indices, GLsizeiptr size)
{
    return CustomSpace::CreateRef<EBO>(indices, size);
}

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}