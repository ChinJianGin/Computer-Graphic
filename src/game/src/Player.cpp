#include"../include/Player.h"
#include"../include/ProjectileSystem.h"

namespace CustomSpace
{
    APlayer::APlayer(const Ref<ShapeFactory>& factory)
    {
        this->Init(factory);
    }

    void APlayer::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Quad>();
        m_Shield = factory->ShapeCreator<Circle>();
        m_Shield->SetScale(glm::vec3(1.15f, 1.15f, -.5));
        if(m_Body == nullptr)
        {
            CORE_ERROR("Player body not set.");
            return;
        }
        m_Body->GetBounding()->SetNeedTest(true);
        m_BoundingVolume = m_Body;
        m_PlayerTex = Texture2D::Create("../src/TextureSrc/PlayerShip.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
        m_PlayerOriginPosition = m_Body->GetTransform()->m_Position;
        for(int i = 0; i < 2; i++)
        {
            m_Satellite[i] = factory->ShapeCreator<Circle>();
            m_Satellite[i]->ModelMatrixMethod(Shape::MatrixMethod::RTS);
            m_Satellite[i]->SetScale(glm::vec3(.25f, .25f, 0));
            CORE_WARN("Create satillite");
        }
        m_Hit = factory->ShapeCreator<Quad>();

        m_ShieldTex = Texture2D::Create("../src/TextureSrc/Shield.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
        m_SatelliteTex = Texture2D::Create("../src/TextureSrc/Satellite.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
        m_HitTex = Texture2D::Create("../src/TextureSrc/Hit.png", GL_TEXTURE_2D, GL_TEXTURE3, GL_UNSIGNED_BYTE);
        m_HP = 30;
        RocketCAL = RocketSAT;
    }

    void APlayer::Update(const CoreTimer& timer)
    {
        m_Orbit += timer.GetFrameTime();

        m_PlayerTex->Bind();
        Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
        m_Body->GetVertexData()->m_Shader->SetInt("tex0", 2);
        if(b_LowHP)
        m_Body->GetVertexData()->m_Shader->SetFloat("U_a", 0.5);
        m_PlayerTex->UnBind();

        glm::vec3 LocalPlayerPosition = m_Body->GetTransform()->m_Position;

        if(damage)
        {
            damagetime += timer.GetTick();
            m_HitTex->Bind();
            m_Hit->SetPosition(glm::vec3(LocalPlayerPosition.x, LocalPlayerPosition.y, -.4f));
            Renderer::Submit(m_Hit->GetVertexData()->m_Shader, m_Hit);
            m_Hit->GetVertexData()->m_Shader->SetInt("tex0", 3);
            m_HitTex->UnBind();
            if(damagetime >= timer.GetDeltaTick())
            {
                damage = false;
                damagetime = 0;
            }
        }

        if(Input::IsKeyDown(GLFW_KEY_Z) && !AttackAgain)
        {
            AttackAgain = true;
            GAME_TRACE("Player Attack");
            Projectile* get;
            for(int i = 0; i < 3; i++)
            {
                get = ProjectileSystem::GetProjectileSystem()->GetFreeList()->front()->get();
                if(get != nullptr)
                {
                    float _y = LocalPlayerPosition.y + (float)(i * (0.3));
                    get->SetTeamID(Projectile::TeamID::Player);
                    get->SetPath(Projectile::Path::Straight);
                    get->SetPosition(glm::vec3(LocalPlayerPosition.x, _y, LocalPlayerPosition.z));
                    ProjectileSystem::GetProjectileSystem()->GetFreeList()->pop_front();
                    ProjectileSystem::GetProjectileSystem()->GetUsedList()->push_front(get);
                }
            }
            CORE_TRACE("In used : {0}", ProjectileSystem::GetProjectileSystem()->GetUsedList()->size());
        }
        else if(AttackAgain)
        {
            SAT -= timer.GetTick();
            if(SAT <= 0)
            {
                AttackAgain = false;
                SAT = 1.f;
            }
        }

        if(ActiveShiled)
        {
            EffectTime += timer.GetTick();
            this->ShieldRender();
            if(EffectTime >= 3)
            {
                EffectTime = 0.f;
                ActiveShiled = false;
                ShiledCooldown = 5.f;
                m_Shield->GetBounding()->SetNeedTest(false);
                m_BoundingVolume = m_Body;
            }
        }

        if(ShiledCooldown > 0 && !ActiveShiled)
        {
            ShiledCooldown -= timer.GetTick();
        }

        if(b_LaunchRocket)
        {
            RocketCAL -= timer.GetTick();
            if(b_Launch)
            {
                Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
                Projectile* get;
                get = ProSystem->GetFreeList()->front()->get();
                if(get != nullptr)
                {
                    float _y = LocalPlayerPosition.y + (float)(2 * (0.3));
                    get->SetTeamID(Projectile::TeamID::Player);
                    get->SetPath(Projectile::Path::ToTarget);
                    get->SetTarget(m_Target);
                    get->SetPosition(glm::vec3(LocalPlayerPosition.x, _y, LocalPlayerPosition.z));
                    ProSystem->GetFreeList()->pop_front();
                    ProSystem->GetUsedList()->push_back(get);
                    RocketCount++;
                }
            }

            if(RocketCount == 2)
            {
                b_Launch = false;
                RocketCount = 0;
            }

            if(RocketCAL <= 0)
            {
                b_LaunchRocket = false;
                RocketCAL = RocketSAT;
            }
        }

        if(m_HP < 15)
        {
            b_LowHP = true;
        }
        else
        {
            b_LowHP = false;
        }
    }

    void APlayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(OnKeyPressedEvent));
    }

    bool APlayer::OnKeyPressedEvent(KeyPressedEvent& event)
    {
        if(event.GetKeyCode() == GLFW_KEY_X && ShiledCooldown <= 0 && !ActiveShiled)
        {
            CORE_INFO("Shiled skill");
            m_Shield->GetBounding()->SetNeedTest(true);
            m_BoundingVolume = m_Shield;
            ActiveShiled = true;
        }    

        if(event.GetKeyCode() == GLFW_KEY_C && !b_LaunchRocket)
        {
            b_LaunchRocket = true;
            b_Launch = true;
        }

       return false;
    }

    void APlayer::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void APlayer::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void APlayer::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void APlayer::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void APlayer::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void APlayer::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void APlayer::ModelMatrixMethod(Shape::MatrixMethod method)
    {
        this->m_Body->ModelMatrixMethod(method);
    }

    void APlayer::AttackAction()
    {
        GAME_INFO("Player attack");
    }

    void APlayer::ShieldRender()
    {
        glm::vec3 LocalPosition = this->m_Body->GetTransform()->m_Position;

        m_ShieldTex->Bind();
        m_Shield->SetPosition(LocalPosition);
        Renderer::Submit(m_Shield->GetVertexData()->m_Shader, m_Shield);
        m_Shield->GetVertexData()->m_Shader->SetInt("tex0", 2);
        m_ShieldTex->UnBind();

        m_Satellite[0]->SetFatherModelMatrix(LocalPosition, true);
        m_Satellite[0]->SetPosition(glm::vec3(.4, .4, -.4));
        m_Satellite[0]->SetRotation(m_Orbit);
        m_Satellite[1]->SetFatherModelMatrix(LocalPosition, true);
        m_Satellite[1]->SetPosition(glm::vec3(-.4, -.4, -.4));
        m_Satellite[1]->SetRotation(m_Orbit);
        m_SatelliteTex->Bind();
        for(int i = 0; i < 2; i++)
        {
           Renderer::Submit(m_Satellite[i]->GetVertexData()->m_Shader, m_Satellite[i]); 
           m_Satellite[i]->GetVertexData()->m_Shader->SetInt("tex0", 2);
        }
        m_SatelliteTex->UnBind();

    }

    void APlayer::Dead()
    {

    }

    void APlayer::TakeDamage()
    {
        if(!ActiveShiled)
        {
            m_HP--;
            damage = true;
        }
    }
}