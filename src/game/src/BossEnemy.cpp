#include"../include/BossEnemy.h"

namespace CustomSpace
{
    BossEnemy::BossEnemy(const Ref<ShapeFactory>& factory)
    {
        this->Init(factory);
    }

    void BossEnemy::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Quad>();
        if(m_Body == nullptr)
        {
            CORE_ERROR("Normal enemy body not set.");
            return;
        }
        m_Body->SetPosition(glm::vec3(0.f, 5.f, -.4f));
        m_Type = EnemyType::Normal;

        m_BossEnemyTex = Texture2D::Create("../src/TextureSrc/BossEnemyShip.png", GL_TEXTURE_2D, GL_TEXTURE10, GL_UNSIGNED_BYTE);
    }

    void BossEnemy::Update(const CoreTimer& timer)
    {
        m_BossEnemyTex->Bind();
        Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
        m_Body->GetVertexData()->m_Shader->SetInt("tex0", 10);
        m_BossEnemyTex->UnBind();
    }

    void BossEnemy::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void BossEnemy::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void BossEnemy::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void BossEnemy::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void BossEnemy::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void BossEnemy::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void BossEnemy::ModelMatrixMethod(const Shape::MatrixMethod method)
    {
        this->m_Body->ModelMatrixMethod(method);
    }

    void BossEnemy::AttackAction()
    {

    }

    void BossEnemy::SetType(EnemyType type)
    {
        m_Type = type;
    }
}