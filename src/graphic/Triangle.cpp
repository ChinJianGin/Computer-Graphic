#include"./Triangle.h"

namespace CustomSpace
{
    Triangle::Triangle()
    {
        this->Init();
    }

    void Triangle::Init()
    {
        m_Transform = CreateRef<Transform>();
        glm::vec3 Points[] =
        {
            glm::vec3(-.5f, -.5f * float(sqrt(3)) / 3, 0.f),
            glm::vec3( .5f, -.5f * float(sqrt(3)) / 3, 0.f),
            glm::vec3( 0.f,  .5f * float(sqrt(3)) * 2 / 3, 0.f)
        };
        m_VertexData = CreateRef<VertexData>(Points, (uint32_t)(sizeof(Points) / sizeof(glm::vec3)));

        glm::vec4 Colors[] =
        {
            glm::vec4( 1.f, 0.f, 0.f, 1.f),
            glm::vec4( .2f, .3f, .8f, 1.f),
            glm::vec4( .8f, .8f, .2f, 1.f),
            glm::vec4(.35f, .9f, .1f, 1.f)
        };
        SetColor(Colors);
    }

    void Triangle::SetPoints(const Ref<VertexData>& data)
    {
        m_VertexData = data;
    }
    
    void Triangle::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform = trans;
    }

    void Triangle::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
    }

    void Triangle::SetColor(const glm::vec4 color[])
    {
       m_Color[0] = color[0];
       m_Color[1] = color[1];
       m_Color[2] = color[2];
       m_Color[3] = color[3];
    }

    void Triangle::SetRotation(const float rotation)
    {
        m_Transform->m_Rotation = rotation;
    }

    void Triangle::SetScale(const float scale)
    {
        m_Transform->m_Scale = scale;
    }
}