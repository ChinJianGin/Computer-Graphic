#include"Line.h"


namespace CustomSpace
{
   Line::Line()
   {
       this->Init();
   } 

    void Line::Init()
    {
        m_Type = Shape::ShapeType::Line;
        m_Method = MatrixMethod::TRS;
        m_Transform = CreateRef<Transform>();
        m_VertexData = CreateRef<VertexData>();
        std::vector<GLfloat> Points = 
        {
            .5f,  0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
            -.5f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f
        };
        m_PointsData = CreateRef<PointsData>();
        m_PointsData->Points.assign(Points.begin(), Points.end());


        std::vector<glm::vec4> Colors = 
        {
            glm::vec4(0.f, 0.f, 1.f, 1.f)
        };
        CORE_WARN("Create Line");
    }
    
    void Line::SetPoints(const Ref<PointsData>& data)
    {
        m_PointsData = data;
        this->LocalUpdate();
    }

    void Line::SetTransform(const Ref<Transform>& trans)
    {
        m_Transform->m_Position = trans->m_Position;
        m_Transform->m_Rotation = trans->m_Rotation;
        m_Transform->m_Scale = trans->m_Scale;
        m_Transform->m_Axis = trans->m_Axis;
        this->LocalUpdate();
    }
    
    void Line::SetPosition(const glm::vec3& pos)
    {
        m_Transform->m_Position = pos;
        this->LocalUpdate();
    }
    
    void Line::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Line::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->m_Rotation = rotation;
        m_Transform->m_Axis = axis;
        this->LocalUpdate();
    }
    
    void Line::SetScale(const glm::vec3& scale)
    {
        m_Transform->m_Scale = scale;
        this->LocalUpdate();
    }

    GLfloat Line::GetLineWidth() const
    {
        return m_LineWidth;
    }

    void Line::SetLineWidth(const GLfloat width)
    {
       m_LineWidth = width;
       glLineWidth(m_LineWidth); 
    }

    void Line::ModelMatrixMethod(const MatrixMethod method)
    {
        m_Method = method;
    }

    void Line::LocalUpdate()
    {
        if(m_Method == MatrixMethod::TRS)
        {
            this->GetTransform()->m_ModelMatrix = glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)
                * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale));

        }
        else
        {
            if(m_Method == MatrixMethod::RTS)
            {
                this->GetTransform()->m_ModelMatrix = glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)                    
                    * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale));
            }
            else
            {
                this->GetTransform()->m_ModelMatrix = glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::translate(glm::mat4(1.f), this->GetTransform()->m_Position)                    
                    * glm::rotate(glm::mat4(1.f), this->GetTransform()->m_Rotation, this->GetTransform()->m_Axis)
                    * glm::scale(glm::mat4(1.f), glm::vec3(this->GetTransform()->m_Scale));
            }
        }
    }
}