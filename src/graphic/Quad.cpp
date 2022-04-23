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
        m_Method = MatrixMethod::TRS;
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
        this->LocalUpdate();
    }

    void Quad::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform->m_Position = trans->m_Position;
        m_Transform->m_Rotation = trans->m_Rotation;
        m_Transform->m_Scale = trans->m_Scale;
        m_Transform->m_Axis = trans->m_Axis;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Quad::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Quad::SetPosition(const float pos, int axis)
    {
        switch(axis)
        {
            case 1:
            m_Transform->m_Position.x = pos;
            break;

            case 2:
            m_Transform->m_Position.y = pos;
            break;

            default:
            break;
        }

        m_Bounding->ResizeBoundingVolume(m_Transform);
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

    void Quad::SetScale(const glm::vec3& scale)
    {
        m_Transform->m_Scale = scale;
        m_Bounding->ResizeBoundingVolume(m_Transform);
        this->LocalUpdate();
    }

    void Quad::ModelMatrixMethod(const MatrixMethod method)
    {
        m_Method = method;
    }
    
    void Quad::LocalUpdate()
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