#include"./LightBox.h"

namespace CustomSpace
{
    LightBox::LightBox()
    {
        this->Init();
    }

    void LightBox::Init()
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
                0, 7, 4,
                0, 3, 7,
                3, 6, 7,
                3, 2, 6,
                2, 5, 6,
                2, 1, 5,
                1, 4, 5,
                1, 0, 4,
                4, 6, 5,
                4, 7, 6
            };

        m_VertexData->indices.assign(indices, indices + 36);

        CORE_WARN("Create LightBox");
    }

    void LightBox::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
    }

    void LightBox::SetModelMatrix(const glm::mat4 &model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void LightBox::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void LightBox::SetPosition(const glm::vec3 &pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void LightBox::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void LightBox::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void LightBox::SetScale(const glm::vec3 &scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}