#include "./Box.h"

namespace CustomSpace
{
    Box::Box()
    {
        this->Init();
    }

    void Box::Init()
    {
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        m_Type = ShapeType::Model;
        std::vector<GLfloat> Points =
            {
                -.5f, -.5f, -.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
                .5f, .5f, -.5f, 0.f, 0.f, -1.f, 1.f, 1.f,
                .5f, -.5f, -.5f, 0.f, 0.f, -1.f, 1.f, 0.f,
                -.5f, .5f, -.5f, 0.f, 0.f, -1.f, 0.f, 1.f,

                -.5f, -.5f, .5f, 0.f, 0.f, 1.f, 0.f, 0.f,
                .5f, -.5f, .5f, 0.f, 0.f, 1.f, 1.f, 0.f,
                .5f, .5f, .5f, 0.f, 0.f, 1.f, 1.f, 1.f,
                -.5f, .5f, .5f, 0.f, 0.f, 1.f, 0.f, 1.f,

                -.5f, .5f, .5f, -1.f, 0.f, 0.f, 1.f, 0.f,
                -.5f, .5f, -.5f, -1.f, 0.f, 0.f, 1.f, 1.f,
                -.5f, -.5f, -.5f, -1.f, 0.f, 0.f, 0.f, 1.f,
                -.5f, -.5f, .5f, -1.f, 0.f, 0.f, 0.f, 0.f,

                .5f, .5f, .5f, 1.f, 0.f, 0.f, 1.f, 0.f,
                .5f, -.5f, -.5f, 1.f, 0.f, 0.f, 0.f, 1.f,
                .5f, .5f, -.5f, 1.f, 0.f, 0.f, 1.f, 1.f,
                .5f, -.5f, .5f, 1.f, 0.f, 0.f, 0.f, 0.f,

                -.5f, -.5f, -.5f, 0.f, -1.f, 0.f, 0.f, 1.f,
                .5f, -.5f, -.5f, 0.f, -1.f, 0.f, 1.f, 1.f,
                .5f, -.5f, .5f, 0.f, -1.f, 0.f, 1.f, 0.f,
                -.5f, -.5f, .5f, 0.f, -1.f, 0.f, 0.f, 0.f,

                -.5f, .5f, -.5f, 0.f, 1.f, 0.f, 0.f, 1.f,
                .5f, .5f, .5f, 0.f, 1.f, 0.f, 1.f, 0.f,
                .5f, .5f, -.5f, 0.f, 1.f, 0.f, 1.f, 1.f,
                -.5f, .5f, .5f, 0.f, 1.f, 0.f, 0.f, 0.f};
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        GLuint indices[] =
            {
                0, 1, 2,
                1, 0, 3,
                4, 5, 6,
                4, 6, 7,
                8, 9, 10,
                8, 10, 11,
                12, 13, 14,
                12, 15, 13,
                16, 17, 18,
                16, 18, 19,
                20, 21, 22,
                20, 23, 21};

        m_VertexData->indices.assign(indices, indices + 36);

        CORE_WARN("Create Box");
    }

    void Box::SetPoints(const Ref<PointsData> &data)
    {
        m_PointsData = data;
    }

    void Box::SetModelMatrix(const glm::mat4 &model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Box::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void Box::SetPosition(const glm::vec3 &pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void Box::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Box::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void Box::SetScale(const glm::vec3 &scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}