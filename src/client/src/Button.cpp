#include "../include/Button.h"
#include "../../graphic/Quad.h"
namespace CustomSpace
{
    Button::Button()
    {
        this->Init();
    }

    void Button::Init()
    {
        m_Body = ShapeFactory::Get().ShapeCreator<Quad>();
        m_OriginLB = glm::vec3(m_Body->GetPointsData()->Points[0], m_Body->GetPointsData()->Points[1], m_Body->GetPointsData()->Points[2]);
        m_OriginRT = glm::vec3(m_Body->GetPointsData()->Points[24], m_Body->GetPointsData()->Points[25], m_Body->GetPointsData()->Points[26]);
    }

    void Button::OnUpdate(CoreTimer &timer)
    {
    }

    bool Button::OnClicked(const glm::vec2 &cpos)
    {
        if (cpos.x >= m_WorldLB.x && cpos.x <= m_WorldRT.x && cpos.y >= m_WorldLB.y && cpos.y <= m_WorldRT.y)
        {
            CORE_INFO("Clicked the button");
            return true;
        }

        return false;
    }

    bool Button::OnHover(const glm::vec2 &hpos)
    {
        if (hpos.x >= m_WorldLB.x && hpos.x <= m_WorldRT.x && hpos.y >= m_WorldLB.y && hpos.y <= m_WorldRT.y)
        {
            return true;
        }

        return false;
    }

    void Button::SetPosition(const glm::vec3 &pos)
    {
        m_Body->SetPosition(pos);
    }

    void Button::SetRotation(const float rotation, const glm::vec3 &axis)
    {
        m_Body->SetRotation(rotation, axis);
    }

    void Button::SetScale(const glm::vec3 &scale)
    {
        m_Body->SetScale(scale);
    }

    void Button::SetModelMatrix(const glm::mat4 &model)
    {
        m_Body->SetModelMatrix(model);
        m_WorldLB = glm::vec3(model * glm::vec4(m_OriginLB, 1.f));
        m_WorldRT = glm::vec3(model * glm::vec4(m_OriginRT, 1.f));
    }

    void Button::SetParentTransform(const Ref<Transform> &parent)
    {
        m_Body->SetParentTransform(parent);
    }
}