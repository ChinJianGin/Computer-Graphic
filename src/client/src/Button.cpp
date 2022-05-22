#include"../include/Button.h"
#include"../../graphic/Quad.h"
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

    void Button::OnUpdate(CoreTimer& timer)
    {

    }

    bool Button::OnClicked(const glm::vec2& cpos)
    {
        return false;
    }

    void Button::SetPosition(const glm::vec3& pos)
    {
        m_Body->SetPosition(pos);
    }

    void Button::SetRotation(const float rotation, const glm::vec3& axis)
    {
        m_Body->SetRotation(rotation, axis);
    }

    void Button::SetScale(const glm::vec3& scale)
    {
        m_Body->SetScale(scale);
    }

    void Button::SetModelMatrix(const glm::mat4& model)
    {
        m_Body->SetModelMatrix(model);
        m_WorldLB = glm::vec3(model * glm::vec4(m_OriginLB, 1.f));
        CORE_WARN("World LB X : {0} , Y : {1}", m_WorldLB.x, m_WorldLB.y);
        m_WorldRT = glm::vec3(model * glm::vec4(m_OriginRT, 1.f));
        CORE_WARN("World RT X : {0} , Y : {1}", m_WorldRT.x, m_WorldRT.y);
    }

    void Button::SetParentTransform(const Ref<Transform>& parent)
    {
        m_Body->SetParentTransform(parent);
    }
}