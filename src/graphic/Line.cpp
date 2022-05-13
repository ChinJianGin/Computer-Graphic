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
    }

    void Line::SetModelMatrix(const glm::mat4& model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void Line::SetPosition(const glm::vec3& pos)
    {
        m_Transform->SetPosition(pos);
    }

    void Line::SetColor(const std::vector<glm::vec4> colors)
    {
        m_Color.assign(colors.begin(), colors.end());
    }

    void Line::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Transform->SetRotation(rotation, axis);
    }
    
    void Line::SetScale(const glm::vec3& scale)
    {
        m_Transform->SetScaleValue(scale);
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
}