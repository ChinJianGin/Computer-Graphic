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
        std::vector<GLfloat> Points =
        {
            -.5f, -.5f, 0.f, .8f, .2f, .1f, 0.f, 0.f,
            -.5f,  .5f, 0.f, .1f, .8f, .2f, 0.f, 1.f,
             .5f, -.5f, 0.f, .2f, .1f, .8f, 1.f, 0.f,
             .5f,  .5f, 0.f, .3f, .6f, .9f, 1.f, 1.f
        };
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        GLuint indices[] = 
        {
            2, 1, 0,
            2, 3, 1
        };

        m_VertexData->indices.assign(indices, indices + 6);

        m_Bounding = CreateRef<BoundingObject>(m_Transform, m_PointsData);

        std::vector<glm::vec4> Colors =
        {
            glm::vec4( 1.f, 0.f, 0.f, 1.f),
            glm::vec4( .2f, .3f, .8f, 1.f),
            glm::vec4( .8f, .8f, .2f, 1.f),
            glm::vec4(.35f, .9f, .1f, 1.f)
        };
        SetColor(Colors);
        CORE_WARN("Create Quad");
    }

    void Quad::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
    }

    void Quad::SetModelMatrix(const glm::mat4& model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Quad::SetParentTransform(const Ref<Transform>& parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void Quad::SetPosition(const glm::vec3& pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void Quad::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Quad::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void Quad::SetScale(const glm::vec3& scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}