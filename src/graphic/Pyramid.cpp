#include "./Pyramid.h"

namespace CustomSpace
{
    Pyramid::Pyramid()
    {
        this->Init();
    }

    void Pyramid::Init()
    {
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        std::vector<GLfloat> Points =
            {
                -.5f, 0.f, .5f, .83f, .7f, .44f, 0.f, 0.f,
                -.5f, 0.f, -.5f, .83f, .7f, .44f, 5.f, 0.f,
                .5f, 0.f, -.5f, .83f, .7f, .44f, 0.f, 0.f,
                .5f, 0.f, .5f, .83f, .7f, .44f, 5.f, 0.f,
                0.f, .8f, 0.f, .92f, .86f, .76f, 2.5f, 5.f};
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        GLuint indices[] =
            {
                0, 1, 2,
                0, 2, 3,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4};

        m_VertexData->indices.assign(indices, indices + 18);

        m_Bounding = CreateRef<BoundingObject>(m_Transform, m_PointsData);

        std::vector<glm::vec4> Colors =
            {
                glm::vec4(1.f, 0.f, 0.f, 1.f),
                glm::vec4(.2f, .3f, .8f, 1.f),
                glm::vec4(.8f, .8f, .2f, 1.f),
                glm::vec4(.35f, .9f, .1f, 1.f)};
        SetColor(Colors);
        CORE_WARN("Create Pyramid");
    }

    void Pyramid::SetPoints(const Ref<PointsData> &data)
    {
        m_PointsData = data;
    }

    void Pyramid::SetModelMatrix(const glm::mat4 &model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Pyramid::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Transform->SetParentTransform(parent);
    }

    void Pyramid::SetPosition(const glm::vec3 &pos)
    {
        m_Transform->SetPosition(pos);
        m_Bounding->ResizeBoundingVolume(m_Transform);
    }

    void Pyramid::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Pyramid::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }

    void Pyramid::SetScale(const glm::vec3 &scale)
    {
        m_Transform->SetScaleValue(scale);
    }
}