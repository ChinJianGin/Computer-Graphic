#include"./Plane.h"

namespace CustomSpace
{
    Plane::Plane()
    {
        this->Init();
    }

    void Plane::Init()
    {
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        m_Type = ShapeType::Model;
        std::vector<GLfloat> Points =
            {
                -1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f,
                -1.f, 0.f, -1.f, 0.f, -1.f, 0.f, 0.f, 1.f,
                1.f, 0.f, -1.f, 0.f, -1.f, 0.f, 1.f, 1.f,
                1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f, 0.f};
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        GLuint indices[] =
            {
                0, 1, 2,
                0, 2, 3
            };

        m_VertexData->indices.assign(indices, indices + 6);

        CORE_WARN("Create Plane");
    }

    void Plane::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
    }

    void Plane::SetModelMatrix(const glm::mat4 &model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Plane::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void Plane::SetPosition(const glm::vec3 &pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void Plane::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Plane::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void Plane::SetScale(const glm::vec3 &scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}