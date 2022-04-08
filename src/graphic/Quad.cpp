#include"Quad.h"

namespace CustomSpace
{
    Quad::Quad()
    {
        this->Init();
    }

    void Quad::Init()
    {
        m_Type  = ShapeType::Quad;
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        std::vector<glm::vec3> Points =
        {
            glm::vec3(-.5f, -.5f, 0.f),glm::vec3( .8f, .2f, .1f),
            glm::vec3(-.5f,  .5f, 0.f),glm::vec3( .1f, .2f, .6f),
            glm::vec3( .5f, -.5f, 0.f),glm::vec3( .2f, .7f, .1f),
            glm::vec3( .5f,  .5f, 0.f),glm::vec3( .3f, .25f, .6f)
        };
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        std::vector<glm::vec4> Colors =
        {
            glm::vec4( 1.f, 0.f, 0.f, 1.f),
            glm::vec4( .2f, .3f, .8f, 1.f),
            glm::vec4( .8f, .8f, .2f, 1.f),
            glm::vec4(.35f, .9f, .1f, 1.f)
        };
        CORE_WARN("Create Quad");
    }

    void Quad::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
        this->LocalUpdate();
    }

    void Quad::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform =  trans;
        this->LocalUpdate();
    }

    void Quad::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
        this->LocalUpdate();
    }

    void Quad::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Quad::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->m_Rotation = rotation;
        m_Transform->m_Axis = axis;
        this->LocalUpdate();
    }

    void Quad::SetScale(const float scale)
    {
        m_Transform->m_Scale = scale;
        this->LocalUpdate();
    }
    
    void Quad::LocalUpdate()
    {
        this->GetTransform()->m_ModelMatrix = glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)
        * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
        * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale));
    }
}