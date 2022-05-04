#include"../include/Scene.h"

namespace CustomSpace
{
    Scene::Scene()
    {
        this->Init();
    }

    Scene::~Scene()
    {

    }

    void Scene::Init()
    {
        m_OriginTransform[0] = glm::vec3(0, -9.6, -1);
        m_OriginTransform[1] = glm::vec3(0, 0, -1);
        m_OriginTransform[2] = glm::vec3(0, 9.6, -1);
        m_Factory = CreateRef<ShapeFactory>();        

        Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem(m_Factory);
        if(ProSystem == nullptr)
        {
            return;
        }

        CORE_INFO("Projectile num : {0}", ProSystem->GetProjectileList()->size());
        
        m_Background = m_Factory->ShapeCreator<Quad>();
        m_Background->SetPosition(m_OriginTransform[1]);
        m_Background->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture = Texture2D::Create("../src/TextureSrc/T_PurpleBackground_Version1_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

        m_Background2 = m_Factory->ShapeCreator<Quad>();
        m_Background2->SetPosition(m_OriginTransform[2]);
        m_Background2->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture2 = Texture2D::Create("../src/TextureSrc/T_YellowBackground_Version1_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);

        m_CollisionTest = m_Factory->ShapeCreator<Quad>();
        m_CollisionTest->SetPosition(glm::vec3(2, 3, 0));
        m_CollisionTest->GetBounding()->SetNeedTest(true);

        m_Player = CreateRef<APlayer>(m_Factory);
        m_Transform = glm::vec3(0, -3.5, -.5);
        if(m_Player != nullptr)
        {
            m_Player->SetPosition(m_Transform);
            m_Player->SetScale(glm::vec3(.45, .55, 0));
        }

        m_Normal = CreateRef<NormalEnemy>(m_Factory);
        if(m_Normal != nullptr)
        {
            m_Normal->SetPosition(glm::vec3(0.f, 3.f, -.4f));
        }

        m_Elite = CreateRef<EliteEnemy>(m_Factory);
        if(m_Elite != nullptr)
        {
            m_Elite->SetPosition(glm::vec3(-2, 3, -.4f));
        }

        m_Boss = CreateRef<BossEnemy>(m_Factory);
        if(m_Boss != nullptr)
        {
            m_Boss->SetPosition(glm::vec3(-2, 2, -.4f));
        }
    }
    void Scene::Update(CoreTimer& time)
    {
        m_FrameTime += time.GetFrameTime();
        m_RunTime += time.GetTick();
        m_Texture->Bind();
        CustomSpace::Renderer::Submit(m_Background->GetVertexData()->m_Shader, m_Background);
        m_Background->GetVertexData()->m_Shader->SetInt("tex0", 0);
        m_Texture->UnBind();
        m_Texture2->Bind();
        CustomSpace::Renderer::Submit(m_Background2->GetVertexData()->m_Shader, m_Background2);
        m_Background2->GetVertexData()->m_Shader->SetInt("tex0", 1);
        m_Texture2->UnBind();

        if(m_FrameTime >= time.GetDeltaTick())
        {
            float CurrentPos = m_Background->GetTransform()->m_Position.y;
            CurrentPos -= (time.GetTick() * m_MoveSpeed);

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background->SetPosition(CurrentPos, 2);

            CurrentPos = m_Background2->GetTransform()->m_Position.y;
            CurrentPos -= time.GetTick() * m_MoveSpeed;

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background2->SetPosition(CurrentPos, 2);
            m_FrameTime -= time.GetDeltaTick();
        }

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_LEFT))
            m_Transform.x -= (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_RIGHT))
            m_Transform.x += (float)m_PlayerSpeed * time.GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_UP))
            m_Transform.y += (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_DOWN))
            m_Transform.y -= (float)m_PlayerSpeed * time.GetTick();

        m_Player->SetPosition(m_Transform);
        m_Player->Update(time);
        m_Normal->SetTarget(m_Player);
        m_Normal->Update(time);
        m_Elite->Update(time);
        m_Boss->Update(time);
        Renderer::Submit(m_CollisionTest->GetVertexData()->m_Shader, m_CollisionTest);
        if(m_Player->GetBounding()->Intersects(m_CollisionTest->GetBounding()))
        {
            CORE_WARN("Collide : {0}", m_Player->GetBounding()->GetBoundingVolume()->Radius_NS);
        }

        Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
        for(auto it = ProSystem->GetInUsedList()->begin(); it != ProSystem->GetInUsedList()->end(); ++it)
        {
            if(it != nullptr)
            {
                it.Get()->Update(time);
                if(it.Get()->GetTransform()->m_Position.y > 5.f || it.Get()->GetTransform()->m_Position.y < -5.f)
                {
                    it.Get()->SetTeamID(Projectile::TeamID::Neutral);
                    ProSystem->GetInUsedList()->Delete(it.Get());
                    ProSystem->GetProjectileList()->Push_back(it.Get());
                    CORE_TRACE("List : {0}", ProSystem->GetProjectileList()->size());
                }
            }
        }
    }

    void Scene::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(Scene::OnKeyPressedEvent));

        m_Player->OnEvent(event);
    }

    bool Scene::OnKeyPressedEvent(KeyPressedEvent& event)
    {
        return false;
    }
}