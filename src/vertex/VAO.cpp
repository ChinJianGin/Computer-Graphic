#include"VAO.h"

namespace CustomSpace
{
    static GLenum ShaderTypeToOpenGLType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::i_Vec:     return GL_INT;
            case ShaderDataType::i_Vec2:    return GL_INT;
            case ShaderDataType::i_Vec3:    return GL_INT;
            case ShaderDataType::i_Vec4:    return GL_INT;
            case ShaderDataType::f_Vec:     return GL_FLOAT;
            case ShaderDataType::f_Vec2:    return GL_FLOAT;
            case ShaderDataType::f_Vec3:    return GL_FLOAT;
            case ShaderDataType::f_Vec4:    return GL_FLOAT;
            case ShaderDataType::Bool:      return GL_BOOL;
            default: std::cout << "Unknown ShaderDataType" << std::endl;
        }
        return 0;
    }
}

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttribute(VBO VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponent, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.UnBind();
}

void VAO::AddVBO(const CustomSpace::Ref<VBO>& vbo)
{
    if(vbo->GetLayout().GetElements().size() < 0) std::cout << "Vertex Buffer has no layout" << std::endl;

    glBindVertexArray(ID);
    vbo->Bind();
    GLuint index = 0;
    const auto& layout = vbo->GetLayout();
    for(const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.GetNumComponent(),
            CustomSpace::ShaderTypeToOpenGLType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)element.Offset
        );
        index++;
    }
    m_VBO.push_back(vbo);
}

void VAO::SetEBO(const CustomSpace::Ref<EBO>& ebo)
{
    glBindVertexArray(ID);
    ebo->Bind();

    m_EBO =  ebo;
}

void VAO::Bind() const
{
    glBindVertexArray(ID);
}

void VAO::UnBind() const
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}