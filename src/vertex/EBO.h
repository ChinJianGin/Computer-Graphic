#pragma once
#include"../core/include/Core.h"
#include<glad/glad.h>

class EBO
{
public:
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind() const;
    void UnBind() const;
    void Delete();

    GLuint GetCount() const { return m_size; }

    static CustomSpace::Ref<EBO> Create(GLuint* indices, GLsizeiptr size);
private:
    GLuint ID;
    GLsizeiptr m_size;
};