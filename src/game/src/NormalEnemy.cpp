#include"../include/NormalEnemy.h"

namespace CustomSpace
{
    NormalEnemy::NormalEnemy(const Ref<ShapeFactory>& factory)
    {
        this->Init(factory);
    }

    void NormalEnemy::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Quad>();
        if(m_Body == nullptr)
        {
            CORE_ERROR("Normal enemy body not set.");
            return;
        }
        m_Body->SetPosition(glm::vec3(0.f, 5.f, -.4f));
        m_Body->SetScale(glm::vec3(.3f, .3f, 1));
        m_Type = EnemyType::Normal;

        m_NormalEnemyTex = Texture2D::Create("../src/TextureSrc/NormalEnemyShip.png", GL_TEXTURE_2D, GL_TEXTURE10, GL_UNSIGNED_BYTE);
        m_Cal = m_SAT;
    }

    void NormalEnemy::Update(const CoreTimer& timer)
    {
        if(b_Enable)
        {
            m_NormalEnemyTex->Bind();
            Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
            m_Body->GetVertexData()->m_Shader->SetInt("tex0", 10);
            m_NormalEnemyTex->UnBind();

            glm::vec3 LocalPosition = m_Body->GetTransform()->m_Position;
            m_Cal -= timer.GetTick();
            if(m_Cal <= 0)
            {
                Projectile* get;
                Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
                get = ProSystem->GetFreeList()->front()->get();
                if(get != nullptr)
                {
                    get->SetTeamID(Projectile::TeamID::Enemy);
                    get->SetTarget(m_Target);
                    get->SetPosition(LocalPosition);
                    ProSystem->GetFreeList()->pop_front();
                    ProSystem->GetUsedList()->push_back(get);
                }
                GAME_INFO("Normal attack");
                m_Cal = m_SAT;
            }
        }
    }

    void NormalEnemy::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void NormalEnemy::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void NormalEnemy::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void NormalEnemy::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void NormalEnemy::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void NormalEnemy::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void NormalEnemy::ModelMatrixMethod(const Shape::MatrixMethod method)
    {
        this->m_Body->ModelMatrixMethod(method);
    }

    void NormalEnemy::AttackAction()
    {

    }

    void NormalEnemy::SetType(EnemyType type)
    {
        m_Type = type;
    }
}