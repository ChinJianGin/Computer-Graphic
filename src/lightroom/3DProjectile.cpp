#include"./3DProjectile.h"
#include"../client/include/Creator.h"
#include"../graphic/LightBox.h"
#include"../graphic/Renderer.h"

namespace CustomSpace
{
    Bullet::Bullet()
    {
        this->Init();
    }

    Bullet::~Bullet()
    {

    }

    void Bullet::Init()
    {
        m_OriginPos = glm::vec3(0.f);
        m_CurrentPos = m_OriginPos;
        m_Direction = glm::vec3(0.f, 0.f, -1.f);

        m_Acceleration = 5.f;
        m_RunTime = 0.f;
        m_Body = ShapeFactory::Get().ShapeCreator<LightBox>();
    }

    void Bullet::Update(CoreTimer& timer)
    {
        m_RunTime += timer.GetTick();
        m_CurrentPos = m_OriginPos + (m_RunTime * m_Acceleration * m_Direction);
        m_Body->SetPosition(m_CurrentPos);
        glm::mat4 _MM = this->GetTransform()->GetTranslate() * this->GetTransform()->GetRotate() * this->GetTransform()->GetScale();
        this->SetModelMatrix(_MM); 
    }

    void Bullet::SetModelMatrix(const glm::mat4& model)
    {
        m_Body->SetModelMatrix(model);
    }

    void Bullet::SetPosition(const glm::vec3& pos)
    {
        m_Body->SetPosition(pos);
        m_OriginPos = pos;
    }

    void Bullet::SetRotation(const float radians, const glm::vec3& axis)
    {
        m_Body->SetRotation(radians, axis);
    }

    void Bullet::SetScale(const glm::vec3& scale)
    {
        m_Body->SetScale(scale);
    }

    void Bullet::SetDirection(const glm::vec3& direct)
    {
        m_Direction = direct;
    }

    void Bullet::SetAcceleration(const float acceleration)
    {
        m_Acceleration = acceleration;
    }

    void Bullet::Reset()
    {
        m_RunTime = 0.f;
    }
}