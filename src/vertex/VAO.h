#pragma once
#include "../core/include/Core.h"
#include "EBO.h"
#include "VBO.h"
#include<glad/glad.h>


class VAO
{
public:
    VAO();

    void AddVBO(const CustomSpace::Ref<VBO>& vbo);
    void SetEBO(const CustomSpace::Ref<EBO>& ebo);

    void LinkAttribute(VBO VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset);

    const std::vector<CustomSpace::Ref<VBO>>& GetVBO() const { return m_VBO; }
    const CustomSpace::Ref<EBO>& GetEBO() const { return m_EBO; }
    void Bind() const;
    void UnBind() const;
    void Delete();

    static CustomSpace::Ref<VAO> Create();
private:
    GLuint ID;
    GLuint m_Index = 0;
    std::vector<CustomSpace::Ref<VBO>> m_VBO;
    CustomSpace::Ref<EBO> m_EBO;
};

inline CustomSpace::Ref<VAO> VAO::Create()
{
    return CustomSpace::CreateRef<VAO>();
}