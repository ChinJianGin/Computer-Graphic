#include "./Triangle.h"

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
                -.5f, -.5f * float(sqrt(3)) / 3, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
                .5f, -.5f * float(sqrt(3)) / 3, 0.f, .2f, .3f, .8f, 1.f, 0.f,
                0.f, .5f * float(sqrt(3)) * 2 / 3, 0.f, .35f, .9f, .1f, .5f, 1.f};
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        m_Bounding = CreateRef<BoundingObject>(m_Transform, m_PointsData);

        std::vector<glm::vec4> Colors =
            {
                glm::vec4(1.f, 0.f, 0.f, 1.f),
                glm::vec4(.2f, .3f, .8f, 1.f),
                glm::vec4(.8f, .8f, .2f, 1.f),
                glm::vec4(.35f, .9f, .1f, 1.f)};
        SetColor(Colors);
        CORE_WARN("Create Triangle");
    }

    void Triangle::SetPoints(const Ref<PointsData> &data)
    {
        m_PointsData = data;
    }

    void Triangle::SetModelMatrix(const glm::mat4 &model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Triangle::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void Triangle::SetPosition(const glm::vec3 &pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void Triangle::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Triangle::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void Triangle::SetScale(const glm::vec3 &scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}