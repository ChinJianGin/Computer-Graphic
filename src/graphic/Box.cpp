#include"./Box.h"

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
        m_Type = ShapeType::Light;
        std::vector<GLfloat> Points =
            {
                -.1f, -.1f, .1f,
                -.1f, -.1f, -.1f,
                 .1f, -.1f, -.1f,
                .1f, -.1f, .1f,
                -.1f, .1f, .1f,
                -.1f, .1f, -.1f,
                .1f, .1f, -.1f,
                .1f, .1f, .1f
            };
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        GLuint indices[] =
            {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
            };

        m_VertexData->indices.assign(indices, indices + 36);

        CORE_WARN("Create Box");
    }

    void Box::SetPoints(const Ref<PointsData>& data)
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