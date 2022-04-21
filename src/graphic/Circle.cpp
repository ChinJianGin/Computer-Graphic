#include"Circle.h"

namespace CustomSpace
{
    Circle::Circle()
    {
        this->Init();
    }

    void Circle::Init()
    {
        m_Type = ShapeType::Circle;
        m_Method = MatrixMethod::TRS;
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        std::vector<GLfloat> Points =
        {
            -.5f, -.5f, 0.f, 0.f, .9f, .2f, 0.f, 0.f,
            -.5f,  .5f, 0.f, 0.f, .4f, 0.f, 0.f, 1.f,
             .5f, -.5f, 0.f, 0.f, 0.f, .8f, 1.f, 0.f,
             .5f,  .5f, 0.f, .2f, .5f, .3f, 1.f, 1.f
        };
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());

        m_Bounding = CreateRef<BoundingObject>(m_Transform, m_PointsData, true);

        std::vector<glm::vec4> Colors =
        {
            glm::vec4( 1.f, 0.f, 0.f, 1.f),
            glm::vec4( .2f, .3f, .8f, 1.f),
            glm::vec4( .8f, .8f, .2f, 1.f),
            glm::vec4(.35f, .9f, .1f, 1.f)
        };
        SetColor(Colors);
        CORE_WARN("Create Circle");
    }

    void Circle::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
        this->LocalUpdate();
    }

    void Circle::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform->m_Position = trans->m_Position;
        m_Transform->m_Rotation = trans->m_Rotation;
        m_Transform->m_Scale = trans->m_Scale;
        m_Transform->m_Axis = trans->m_Axis;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Circle::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Circle::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Circle::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->m_Rotation = rotation;
        m_Transform->m_Axis = axis;
        this->LocalUpdate();
    }

    void Circle::SetScale(const glm::vec3& scale)
    {
        m_Transform->m_Scale = scale;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Circle::ModelMatrixMethod(const MatrixMethod method) 
    {
        m_Method = method;
    }

    void Circle::LocalUpdate()
    {
        if(m_Method == MatrixMethod::TRS)
        {
            this->GetTransform()->m_ModelMatrix = glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)
                * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale.x, this->GetTransform()->m_Scale.y, this->GetTransform()->m_Scale.z));
        }
        else
        {
            if(m_Method == MatrixMethod::RTS)
            {
                this->GetTransform()->m_ModelMatrix = glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)                    
                    * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale.x, this->GetTransform()->m_Scale.y, this->GetTransform()->m_Scale.z));
 
            }
            else
            {
                this->GetTransform()->m_ModelMatrix = glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)                    
                    * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale.x, this->GetTransform()->m_Scale.y, this->GetTransform()->m_Scale.z));
            }
        }
    }
}