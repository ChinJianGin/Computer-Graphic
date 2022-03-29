#include"VBO.h"

namespace CustomSpace
{
    void BufferLayout::CalculateOffsetAndStride()
    {
        GLuint offset = 0;
        m_Stride = 0;
        for(auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    void BufferLayout::CalculateTightOffset()
    {
        GLuint offset = 0;
        for(auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
        }
    }
}



VBO::VBO(GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}

CustomSpace::Ref<VBO> VBO::Create(GLsizeiptr size)
{
    return CustomSpace::CreateRef<VBO>(size);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}