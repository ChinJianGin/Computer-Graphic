#include"./Triangle.h"

namespace CustomSpace
{
    Triangle::Triangle()
    {
        this->Init();
    }

    void Triangle::Init()
    {   
        m_Type = Shape::ShapeType::Triangle;
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        std::vector<GLfloat> Points =
        {
            -.5f, -.5f * float(sqrt(3)) / 3, 0.f,      1.f, 0.f, 0.f,
             .5f, -.5f * float(sqrt(3)) / 3, 0.f,      .2f, .3f, .8f,
             0.f,  .5f * float(sqrt(3)) * 2 / 3, 0.f, .35f, .9f, .1f
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
        SetColor(Colors);
        CORE_WARN("Create Triangle");
    }

    void Triangle::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
        this->LocalUpdate();
    }
    
    void Triangle::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform = trans;
        this->LocalUpdate();
    }

    void Triangle::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
        this->LocalUpdate();
    }

    void Triangle::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Triangle::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->m_Rotation = rotation;
        m_Transform->m_Axis = axis;
        this->LocalUpdate();
    }

    void Triangle::SetScale(const float scale)
    {
        m_Transform->m_Scale = scale;
        this->LocalUpdate();
    }

    void Triangle::LocalUpdate()
    {
        this->GetTransform()->m_ModelMatrix = glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)
             * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
             * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale));
    }
}