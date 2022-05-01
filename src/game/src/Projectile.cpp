#include "../include/Projectile.h"

namespace CustomSpace
{
    Projectile::Projectile()
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
        m_TeamID = TeamID::Neutral;
    }

    void Projectile::Update(const CoreTimer& timer)
    {

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
}