#pragma once
#include"../core/include/Core.h"
#include<glad/glad.h>

namespace  CustomSpace
{
    enum class ShaderDataType
    {
        None = 0, i_Vec, i_Vec2, i_Vec3, i_Vec4, f_Vec, f_Vec2, f_Vec3, f_Vec4, Bool
    };

    static GLsizeiptr ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::i_Vec:     return 4;
            case ShaderDataType::i_Vec2:    return 4 * 2;
            case ShaderDataType::i_Vec3:    return 4 * 3;
            case ShaderDataType::i_Vec4:    return 4 * 4;
            case ShaderDataType::f_Vec:     return 4;
            case ShaderDataType::f_Vec3:    return 4 * 3;
            case ShaderDataType::f_Vec2:    return 4 * 2;
            case ShaderDataType::f_Vec4:    return 4 * 4;
            case ShaderDataType::Bool:      return 1;
            default: std::cout << "Unknown ShaderDataType" << std::endl;
        }

        return 0;
    }

    struct BufferElements
    {
        const char* Name;
        ShaderDataType Type;
        GLsizeiptr Size;
        uint32_t Offset;
        bool Normalized;

        BufferElements() {}

        BufferElements(ShaderDataType type, const char* name, bool normalized = false)
        : Type(type),
          Name(name),
          Size(ShaderDataTypeSize(type)),
          Normalized(normalized),
          Offset(0)
        {}

        uint32_t GetNumComponent() const
        {
            switch (Type)
            {
                case ShaderDataType::i_Vec:     return 1;
                case ShaderDataType::i_Vec2:    return 2;
                case ShaderDataType::i_Vec3:    return 3;
                case ShaderDataType::i_Vec4:    return 4;
                case ShaderDataType::f_Vec:     return 1;
                case ShaderDataType::f_Vec2:    return 2;
                case ShaderDataType::f_Vec3:    return 3;
                case ShaderDataType::f_Vec4:    return 4;
                case ShaderDataType::Bool:      return 1;
                default: std::cout << "Unknown ShaderDataType" << std::endl;
            }
            return 0;
        }
    };

    class BufferLayout
    {
        public:
            BufferLayout() {}

            BufferLayout(std::initializer_list<BufferElements> elements) : m_Elements(elements)
            {
                CalculateOffsetAndStride();
            }

            inline GLuint GetStride() const { return m_Stride; }
            inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }

            std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
            std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }
        private:
            void CalculateOffsetAndStride();
        private:
            std::vector<BufferElements> m_Elements;
            GLuint m_Stride = 0;
    };
}

class VBO
{
public:
    template <typename T>
    VBO(T vertices, GLsizeiptr size);

    VBO(GLsizeiptr size);

    template <typename T>
    void LoadRealData(GLsizeiptr size_1, GLsizeiptr size_2,const T* data);
    void Bind() const;
    void UnBind() const;
    void Delete();

    void SetLayout(const CustomSpace::BufferLayout& layout) { m_Layout = layout; }
    const CustomSpace::BufferLayout& GetLayout() const { return m_Layout; }

    static CustomSpace::Ref<VBO> Create(GLsizeiptr size);

    template <typename T>
    static CustomSpace::Ref<VBO> Create(T* vertices, GLsizeiptr size);
private:
    GLuint ID;
    CustomSpace::BufferLayout m_Layout;
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

template <typename T>
inline CustomSpace::Ref<VBO> VBO::Create(T* vertices, GLsizeiptr size)
{
    return CustomSpace::CreateRef<VBO>(vertices, size);
}