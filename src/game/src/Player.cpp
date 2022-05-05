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

        m_ShieldTex = Texture2D::Create("../src/TextureSrc/Shield.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
        m_SatelliteTex = Texture2D::Create("../src/TextureSrc/Satellite.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    }

    void APlayer::Update(const CoreTimer& timer)
    {
        m_Orbit += timer.GetFrameTime();

        m_PlayerTex->Bind();
        Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
        m_Body->GetVertexData()->m_Shader->SetInt("tex0", 2);
        m_PlayerTex->UnBind();

        m_ShieldTex->Bind();
        m_Shield->SetPosition(m_Body->GetTransform()->m_Position);
        Renderer::Submit(m_Shield->GetVertexData()->m_Shader, m_Shield);
        m_Shield->GetVertexData()->m_Shader->SetInt("tex0", 2);
        m_ShieldTex->UnBind();

        glm::vec3 LocalPlayerPosition = m_Body->GetTransform()->m_Position;

        // float _x = cosf(m_Orbit) * .5f;
        // float _y = sinf(m_Orbit) * .5f;

        m_Satellite[0]->SetFatherModelMatrix(LocalPlayerPosition, true);
        m_Satellite[0]->SetPosition(glm::vec3(.4, .4, -.4));
        m_Satellite[0]->SetRotation(m_Orbit);
        m_Satellite[1]->SetFatherModelMatrix(LocalPlayerPosition, true);
        m_Satellite[1]->SetPosition(glm::vec3(-.4, -.4, -.4));
        m_Satellite[1]->SetRotation(m_Orbit);
        m_SatelliteTex->Bind();
        for(int i = 0; i < 2; i++)
        {
           Renderer::Submit(m_Satellite[i]->GetVertexData()->m_Shader, m_Satellite[i]); 
           m_Satellite[i]->GetVertexData()->m_Shader->SetInt("tex0", 2);
        }
        m_SatelliteTex->UnBind();

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
}