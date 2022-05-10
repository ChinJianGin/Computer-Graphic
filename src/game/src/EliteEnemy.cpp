#include"../include/EliteEnemy.h"

namespace CustomSpace
{
    EliteEnemy::EliteEnemy(const Ref<ShapeFactory>& factory)
    {
        this->Init(factory);
    }

    void EliteEnemy::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Quad>();
        if(m_Body == nullptr)
        {
            CORE_ERROR("Elite enemy body not set.");
            return;
        }
        m_Body->SetPosition(glm::vec3(0.f, 5.f, -4.f));
        m_Body->SetScale(glm::vec3(.45f, .45f, 1));
        m_Type = EnemyType::Elite;

        m_EliteEnemyTex = Texture2D::Create("../src/TextureSrc/EliteEnemyShip.png", GL_TEXTURE_2D, GL_TEXTURE11, GL_UNSIGNED_BYTE);
        m_CAL = m_SAT;
        m_HP = 30;
    }

    void EliteEnemy::Update(const CoreTimer& timer)
    {
        if(b_Enable)
        {
            m_EliteEnemyTex->Bind();
            Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
            m_Body->GetVertexData()->m_Shader->SetInt("tex0", 11);
            m_EliteEnemyTex->UnBind();

            glm::vec3 LocalPosition = m_Body->GetTransform()->m_Position;
            m_CAL -= timer.GetTick();
            if(m_CAL <= 0)
            {
                Projectile* get;
                Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
                for(int i = 0; i < 3; i++)
                {
                    get = ProSystem->GetFreeList()->front()->get();
                    float r_x = (float)(rand() / (RAND_MAX + 1.f)) * 2.f - 1.f;
                    if(get != nullptr)
                    {
                        get->SetTeamID(Projectile::TeamID::Enemy);
                        get->SetPath(Projectile::Path::ShotGun);
                        get->SetRandDirection(glm::vec3(r_x, 0, -.3f));
                        get->SetPosition(LocalPosition);
                        ProSystem->GetFreeList()->pop_front();
                        ProSystem->GetUsedList()->push_back(get);
                    }
                }
                m_CAL = m_SAT;
            } 
        }
    }

    void EliteEnemy::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void EliteEnemy::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void EliteEnemy::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void EliteEnemy::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void EliteEnemy::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void EliteEnemy::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void EliteEnemy::ModelMatrixMethod(const Shape::MatrixMethod method)
    {
        this->m_Body->ModelMatrixMethod(method);
    }

    void EliteEnemy::AttackAction()
    {

    }

    void EliteEnemy::SetType(EnemyType type)
    {
        m_Type = type;
    }

    void EliteEnemy::Behavior(const CoreTimer& timer)
    {
       if(m_OriginPosition == glm::vec3(0)) m_OriginPosition =  m_Body->GetTransform()->m_Position;
       float _x = m_OriginPosition.x + (float)(cosf(m_RunTime));
       float _y = m_OriginPosition.y + (float)(sinf(m_RunTime));
       m_Body->SetPosition(glm::vec3(_x, _y, m_OriginPosition.z));
       m_RunTime += timer.GetTick(); 
    }

    void EliteEnemy::SetOriginPosition(const glm::vec3& origin)
    {

    }

    void EliteEnemy::Dead()
    {

    }

    void EliteEnemy::TakeDamage()
    {

    }
}