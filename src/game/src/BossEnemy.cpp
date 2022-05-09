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
        m_Type = EnemyType::Boss;

        for(int i = 0; i < 2; i++)
        {
            m_Guardian[i] = factory->ShapeCreator<Quad>();
            m_Guardian[i]->SetScale(glm::vec3(.35f, .35f, 1));
        }

        m_BossEnemyTex = Texture2D::Create("../src/TextureSrc/BossEnemyShip.png", GL_TEXTURE_2D, GL_TEXTURE10, GL_UNSIGNED_BYTE);
        m_BossGuardianTex = Texture2D::Create("../src/TextureSrc/BossGuardianShip.png", GL_TEXTURE_2D, GL_TEXTURE11, GL_UNSIGNED_BYTE);
        m_CAL = m_SAT;
        m_TypeOneCal = m_TypeOneSAT;
    }

    void BossEnemy::Update(const CoreTimer& timer)
    {
        if(b_Enable)
        {
            m_BossEnemyTex->Bind();
            Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
            m_Body->GetVertexData()->m_Shader->SetInt("tex0", 10);
            m_BossEnemyTex->UnBind();

            glm::vec3 LocalPosition = m_Body->GetTransform()->m_Position;

            if(b_CanAttack)
            {
                if(m_CAL > 0)
                {
                    m_InerCAL = 0;
                    m_CAL -= timer.GetTick();
                }
                else
                {
                    Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
                    Projectile* get;
                    if(AttackType == 0)
                    {
                        m_TypeOneCal -= timer.GetTick();
                        m_InerCAL += timer.GetTick();
                        if(m_TypeOneCal <= 0)
                        {
                            if(AttackType == 0)
                            {
                                get = ProSystem->GetFreeList()->front()->get();
                                if(get != nullptr)
                                {
                                    get->SetTeamID(Projectile::TeamID::Enemy);
                                    get->SetPath(Projectile::Path::ToTarget);
                                    get->SetTarget(m_Target);
                                    get->SetPosition(LocalPosition);
                                    ProSystem->GetFreeList()->pop_front();
                                    ProSystem->GetUsedList()->push_back(get);
                                }
                            }
                            m_TypeOneCal = m_TypeOneSAT;
                        }
                        if(m_InerCAL >= 5.f)
                        {
                            m_CAL = m_SAT;
                            m_TypeOneCal = m_TypeOneSAT;
                            AttackType = 1;
                        }
                    }
                    else if(AttackType == 1)
                    {
                        for(int i = 0; i < 6; i++)
                        {
                            get = ProSystem->GetFreeList()->front()->get();
                            float r_x = (float)(rand() / (RAND_MAX + 1.f)) - .5f;
                            float _x = LocalPosition.x + ((i % 2) - 0.5f);
                            if(get != nullptr)
                            {
                                get->SetTeamID(Projectile::TeamID::Enemy);
                                get->SetPath(Projectile::Path::ShotGun);
                                get->SetRandDirection(glm::vec3(r_x, 0, -.3f));
                                get->SetPosition(glm::vec3(_x, LocalPosition.y, LocalPosition.z));
                                ProSystem->GetFreeList()->pop_front();
                                ProSystem->GetUsedList()->push_back(get);
                            }
                        }
                        m_CAL = m_SAT;
                        AttackType = 0;
                    }
                }
            }
        }
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

    void BossEnemy::Behavior(const CoreTimer& timer)
    {
        if(!b_DoOnce)
        {
            m_OriginPosition = m_Body->GetTransform()->m_Position;
            b_CanAttack = true;
            b_DoOnce = true;
        }
        float _x = m_OriginPosition.x;
        float _y = m_OriginPosition.y;
        float _z = m_OriginPosition.z;
        float _sin = sinf(m_RunTime);
        float _cos = cosf(m_RunTime);
        _x += _sin * 1.8f;
        _y += _sin * _cos;
        m_Body->SetPosition(glm::vec3(_x, _y, _z));
        m_RunTime += timer.GetTick();
    }

    void BossEnemy::SetOriginPosition(const glm::vec3& origin)
    {

    }

    void BossEnemy::SecondState()
    {
        glm::vec3 LocalBossPosition = m_Body->GetTransform()->m_Position;
        float _x = 1.f * m_Body->GetTransform()->m_Scale.x;
        float _y = 1.f * m_Body->GetTransform()->m_Scale.y;
        m_Guardian[0]->SetFatherModelMatrix(LocalBossPosition, true);
        m_Guardian[0]->SetPosition(glm::vec3(_x, -_y, -.4f));
        m_Guardian[1]->SetFatherModelMatrix(LocalBossPosition, true);
        m_Guardian[1]->SetPosition(glm::vec3(-_x, -_y, -.4f));

        m_BossGuardianTex->Bind();
        for(int i = 0; i < 2; i++)
        {
            Renderer::Submit(m_Guardian[i]->GetVertexData()->m_Shader, m_Guardian[i]);
            m_Guardian[i]->GetVertexData()->m_Shader->SetInt("tex0", 11);
        }
        m_BossGuardianTex->UnBind();
    }
}