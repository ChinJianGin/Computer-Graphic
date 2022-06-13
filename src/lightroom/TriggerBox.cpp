#include"./TriggerBox.h"
#include"../client/include/Creator.h"

namespace CustomSpace
{
    TriggerBox::TriggerBox()
    {
        this->Init();
    }

    TriggerBox::~TriggerBox()
    {

    }

    void TriggerBox::Init()
    {
        m_TR = glm::vec3(.1f); m_BL = glm::vec3(-.1f);
        m_Transform = CreateRef<Transform>();
        m_Body = ShapeFactory::Get().ShapeCreator<LightBox>();
    }

    void TriggerBox::Update(CoreTimer& timer)
    {

    }

    bool TriggerBox::BeginOverlap(const glm::vec3& pos)
    {
        if(pos.x >= m_BL.x && pos.y >= m_BL.y && pos.z >= m_BL.z && pos.x <= m_TR.x && pos.y <= m_TR.y && pos.z <= m_TR.z)
        {
            return true;
        }
        else
            return false;
    }

    bool TriggerBox::EndOverlap(const glm::vec3& pos)
    {
        return true;
    }

    void TriggerBox::SetPosition(const glm::vec3& pos)
    {
        m_Transform->SetPosition(pos);
    }

    void TriggerBox::SetScale(const glm::vec3& scale)
    {
        m_Transform->SetScaleValue(scale);
    }

    void TriggerBox::SetModelMatrix(const glm::mat4& model)
    {
        m_Transform->SetModelMatrix(model);
        m_TR = glm::vec3(model * glm::vec4(m_TR, 1.f));
        m_BL = glm::vec3(model * glm::vec4(m_BL, 1.f));
    }
}