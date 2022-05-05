#include "../include/Projectile.h"

namespace CustomSpace
{
    Projectile::Projectile()
    {
       m_Owner = nullptr;
       m_Target = nullptr; 
    }

    Projectile::~Projectile()
    {

    }

    void Projectile::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Circle>();
        if(m_Body == nullptr)
        {
            CORE_ERROR("Projectile body not set.");
            return;
        }

        m_Body->SetPosition(glm::vec3(0, 0, 0));
        m_Body->SetScale(glm::vec3(.25f, .25f, 1));
        m_TeamID = TeamID::Neutral;
    }

    void Projectile::Update(const CoreTimer& timer)
    {
        if(m_TeamID == TeamID::Player)
        {
            glm::vec3 LocalPos = m_Body->GetTransform()->m_Position;
            float Velocity = (float)5 * timer.GetTick();
            m_Body->SetPosition(glm::vec3(LocalPos.x, LocalPos.y + Velocity, -.3f));
            m_Body->SetRotation(M_PI_4);
            Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
            m_Body->GetVertexData()->m_Shader->SetInt("tex0", 20);
        }
        else
        {
            glm::vec3 LocalPos = m_Body->GetTransform()->m_Position;
            if(m_Target != nullptr)
            {
                glm::vec3 TargetPos = m_Target->GetTransform()->m_Position;
                m_Direction = glm::normalize(TargetPos - LocalPos);
                m_Target = nullptr;
            }

            float Velocity = (float)6 * timer.GetTick();
            m_Body->SetPosition(glm::vec3(LocalPos.x + (m_Direction.x * Velocity),LocalPos.y + (m_Direction.y * Velocity), -.3f));
            Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
            m_Body->GetVertexData()->m_Shader->SetInt("tex0", 21);
        }
    }

    void Projectile::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void Projectile::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void Projectile::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void Projectile::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void Projectile::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void Projectile::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void Projectile::ModelMatrixMethod(const Shape::MatrixMethod method)
    {
        this->m_Body->ModelMatrixMethod(method);
    }

    void Projectile::AttackAction()
    {

    }

    void Projectile::SetTeamID(const TeamID id)
    {
        m_TeamID = id;
    }

    void Projectile::SetOwner(const Ref<Actor> owner)
    {
        m_Owner = owner;
    }

    void Projectile::SetTarget(const Ref<Actor> target)
    {
        m_Target = target;
    }
}